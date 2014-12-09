// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>

#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include "./Tron.h"
#include "./Biker.h"
#include "./Arena.h"

// _____________________________________________________________________________
Tron::Tron(int sizeX, int sizeY, int numOpponents, int speed) {
  // initialize screen
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);

  _status = ONGOING;
  _numOpponents = numOpponents;
  _speed = speed;

  // get window size and adjust arena size if the default value was demanded
  int winWidth, winHeight;
  getmaxyx(stdscr, winHeight, winWidth);
  if (sizeX == 0) {
    sizeX = (winWidth / 2) - 1;
  }
  if (sizeY == 0) {
    sizeY = winHeight - 2;
  }

  arena = new Arena(sizeX, sizeY);
  player = new Biker((sizeX / 4), (sizeY / 5), Biker::Direction::UP, -1);
}

// _____________________________________________________________________________
Tron::~Tron() {
  // "delete arena" conflicts with destructor of arena?
  endwin();
  delete player;
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
        startYPos = (yAl / 5) * 3;
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

  // counter for moving into the current direction without a user input
  int counter = 0;

  while (true) {
    // get user input
    if (_status == ONGOING) {
      int key = getch();

      // if the input is an arrow key turn accordingly
      if (key < 69 & key > 64) {
        player->turn(Biker::Direction(key));
      }
      // TODO(flackbash): keep speed constant for different arena sizes
      if (++counter % (10 * _speed) == 0) {
        // move the computer opponents
        for (auto& computer : _opponents) {
          if (computer->getStatus() == Biker::Status::RACING) {
            computer->turnComputer(computer->getRandomDirection());
            computer->move(arena);
          }
        }

        // move the player
        player->move(arena);
        arena->show();

        // check whether the game is lost
        if (player->getStatus() == Biker::Status::DESTROYED) {
          _status = LOST;
          endGame();
        // check whether the game is won
        } else {
          int oppLeft = 0;
          for (auto& opponent : _opponents) {
            if (opponent->getStatus() == Biker::Status::DESTROYED) {
              oppLeft++;
            }
          }
          if (_numOpponents - oppLeft == 0) {
            _status = WON;
            endGame();
          }
        }
      }
    } else {
      int ch = getch();
      if (ch == 'q') break;
      if (ch == 'r') reset();
    }
    usleep(1000);
  }
}

// _____________________________________________________________________________
void Tron::endGame() {
  int y = arena->getYAl();
  int x = arena->getXAl();

  if (_status == LOST) {
    printf("\x1b[%d;%dHYOU LOST!\n", (y / 2) - 5, x - 4);
  } else if (_status == WON) {
    printf("\x1b[%d;%dHYOU WON!\n", (y / 2) - 5, x - 3);
  }

  printf("\x1b[%d;%dHPress 'Q' to quit.", (y / 2) - 3, x - 8);
  printf("\x1b[%d;%dHPress 'R' to play again.", (y / 2) - 2, x - 11);
  fflush(stdout);
}

// _____________________________________________________________________________
void Tron::reset() {
  clear();
  player->reset();
  for (auto& opponent : _opponents) {
    opponent->reset();
  }
  arena->reset();
  _status = ONGOING;
}

// _____________________________________________________________________________
Tron::GameStatus Tron::getStatus() const {
  return _status;
}
