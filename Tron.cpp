// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>

#include <ncurses.h>
#include <unistd.h>
#include "./Tron.h"
#include "./Biker.h"
#include "./Arena.h"

// _____________________________________________________________________________
Tron::Tron() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  _opponents = 0;
}

// _____________________________________________________________________________
Tron::~Tron() {
  endwin();
}

// _____________________________________________________________________________
Biker* Tron::createOpponent() {
  // TODO(flackbash): solution for start position (and direction)
  _opponents++;
  Biker::Direction direction = Biker::Direction(_opponents + 64);
  Biker* computer = new Biker(5, 5, direction, -_opponents);
  return computer;
}

// _____________________________________________________________________________
void Tron::play() {
  // TODO(flackbash): more opponents should be added with createOpponent later
  Biker* player = new Biker(5, 5, Biker::Direction::UP, -1);
  Biker* computer = new Biker(25, 25, Biker::Direction::DOWN, 1);
  _opponents = 1;

  Arena* arena = new Arena(60, 40);

  // add a wall to the initial position of player
  arena->addWall(player);

  // counter for moving into the current direction without user input
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
      computer->turn(computer->getRandomDirection());
      computer->move(arena);
      player->move(arena);
      arena->show();
      // check if the game is already lost
      if (player->getStatus() == Biker::Status::DESTROYED) {
        _status = LOST;
        break;
      }
    }
    // wait for 10 milliseconds.
    usleep(10 * 1000);
  }
}

// _____________________________________________________________________________
void Tron::endGame() {}


// _____________________________________________________________________________
Tron::GameStatus Tron::getStatus() const {
  return _status;
}
