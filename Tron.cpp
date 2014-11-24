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
}

// _____________________________________________________________________________
Tron::~Tron() {
  endwin();
}

// _____________________________________________________________________________
void Tron::play() {
  Computer* computer;
  Player* player = new Player(5, 5, Biker::Direction::UP, -1);
  Arena* arena = new Arena(30, 30);

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
    if (++counter % 30 == 0) {
      player->move(arena);
      // printf("\x1b[%d;%dH%d\n", 75, 15, counter);
      arena->show();
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
