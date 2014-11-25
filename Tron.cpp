// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>

#include <ncurses.h>
#include <unistd.h>
#include "./Tron.h"
#include "./Biker.h"
#include "./Arena.h"

// _____________________________________________________________________________
Tron::Tron(int sizeX, int sizeY, int numOpponents) {
  // initialize screen
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);

  arena = new Arena(sizeX, sizeY);
  player = new Biker((sizeX / 4), (sizeY / 5), Biker::Direction::UP, -1);
  _numOpponents = numOpponents;
}

// _____________________________________________________________________________
Tron::~Tron() {
  endwin();
  delete player;
  // delete arena;
  for (auto& computer : _opponents) {
    delete computer;
  }
}

// _____________________________________________________________________________
void Tron::addOpponents(int number) {
  // TODO(flackbash): elegant solution for start position
  Biker::Direction startDirection;
  int startXPos;
  int startYPos;
  int xAl = arena->getXAl();
  int yAl = arena->getYAl();


  for (int i = 1; i <= number; i++) {
    startDirection = Biker::Direction((65 + (i % 4)));
    switch (i) {
      case(1):
        startXPos = (xAl / 4) * 3;
        startYPos = (yAl / 5) * 4;
        break;
      case(2):
        startXPos = (xAl / 4) * 1;
        startYPos = (yAl / 5) * 2;
        break;
      case(3):
        startXPos = (xAl / 4) * 3;
        startYPos = (yAl / 5) * 2;
        break;
      case(4):
        startXPos = (xAl / 4) * 2;
        startYPos = (yAl / 5) * 1;
        break;
      case(5):
        startXPos = (xAl / 4) * 2;
        startYPos = (yAl / 5) * 4;
        break;
    }
    Biker* computer = new Biker(startXPos, startYPos, startDirection, i);
    _opponents.push_back(computer);
  }
}

// _____________________________________________________________________________
void Tron::play() {
  addOpponents(_numOpponents);

  // add a wall at the initial position of player
  // arena->addWall(player);

  // counter for moving into the current direction without a user input
  int counter = 0;

  while (true) {
    // long startTime, runTime;
    // startTime = System.currentTimeMillis();
    // runTime = System.currentTimeMillis() - startTime;

    // get user input
    int key = getch();

    // if the input is an arrow key turn accordingly
    if (key < 69 & key > 64) {
      player->turn(Biker::Direction(key));
    }
    if (++counter % 5 == 0) {
      // move the computer opponents
      // TODO(flackbash): change seed for getRandomDirection. Right now all
      // opponents move into the same direction...
      for (auto& computer : _opponents) {
        computer->turn(computer->getRandomDirection());
        computer->move(arena);
      }

      // move the player
      player->move(arena);
      arena->show();

      // check whether the game is already lost
      if (player->getStatus() == Biker::Status::DESTROYED) {
        _status = LOST;
        endGame(arena);
        break;
      }
    }
    // wait for 10 milliseconds.
    usleep(10 * 1000);
  }
}

// _____________________________________________________________________________
void Tron::endGame(Arena* arena) {
  int y = arena->getYAl();
  int x = arena->getXAl();

  if (_status == LOST) {
    printf("\x1b[%d;%dHYOU LOST!\n", (y / 2) - 5, x - 4);
  } else if (_status == WON) {
    printf("\x1b[%d;%dHYOU WON!\n", (y / 2) - 5, x - 3);
  }
  while (true) {
    printf("\x1b[%d;%dHPress 'Q' to quit.", (y / 2) - 3, x - 8);
    printf("\x1b[%d;%dHPress 'R' to play again.", (y / 2) - 2, x - 11);

    int ch = getch();
    if (ch == 'q') break;
    // TODO(flackbash): implement reset()-method for replay
    if (ch == 'r') break;
  }
}

// _____________________________________________________________________________
void Tron::reset() {}

// _____________________________________________________________________________
Tron::GameStatus Tron::getStatus() const {
  return _status;
}
