// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>

#include <stdio.h>
#include "./Arena.h"
#include "./Biker.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define RESET   "\x1b[0m"

// _____________________________________________________________________________
Arena::Arena(size_t x, size_t y) {
  _xAl = x;
  _yAl = y;
  _cells = new CellStatus* [_xAl];
  for (int x = 0; x < _xAl; x++) {
    _cells[x] = new CellStatus[_yAl];
    for (int y = 0; y < _yAl; y++) {
      _cells[x][y] = EMPTY;
    }
  }
}

// _____________________________________________________________________________
Arena::~Arena() {
  for (int i = 0; i < _xAl; i++) { delete _cells[i]; }
  delete[] _cells;
}

// _____________________________________________________________________________
void Arena::addWall(Biker* biker) {
  size_t x = biker->getXPos();
  size_t y = biker->getYPos();
  _cells[x][y] = CellStatus(biker->getNumber());
}

// _____________________________________________________________________________
void Arena::show() {
  // print arena borders
  printf("\x1b[7m");
  printf("%s", RED);
  // horizontal borders
  for (int i = 1; i <= (_xAl * 2) + 2; i++) {
    printf("\x1b[%d;%dH ", 0, i);
    printf("\x1b[%d;%dH ", _yAl + 2, i);
  }
  // vertical borders
  for (int i = 1; i <= _yAl + 1; i++) {
    printf("\x1b[%d;%dH ", i, 1);
    printf("\x1b[%d;%dH ", i, (_xAl * 2) + 2);
  }

  printf("%s", RESET);
  // print the bikers' walls
  for (int y = 0; y < _yAl; y++) {
    for (int x = 0; x < _xAl; x++) {
      for (int s = 0; s < 2; s++) {
        switch (_cells[x][y]) {
          case(EMPTY):
            printf("%s", RESET);
            break;
          case(PLAYER1):
            printf("%s", GREEN);
            break;
          case(COMPUTER1):
            printf("%s", YELLOW);
            break;
          case(COMPUTER2):
            printf("%s", BLUE);
            break;
          case(COMPUTER3):
            printf("%s", MAGENTA);
            break;
          case(COMPUTER4):
            printf("%s", CYAN);
            break;
          case(COMPUTER5):
            printf("%s", WHITE);
            break;
        }
        if (_cells[x][y] != EMPTY) {
          printf("\x1b[7m");
        } else {
          printf("%s", RESET);
        }
        printf("\x1b[%d;%dH ", (_yAl - y) + 1, (x * 2) + 2 + s);
      }
    }
  }
  fflush(stdout);
}

// _____________________________________________________________________________
void Arena::removeWall(Biker* biker) {
  for (int x = 0; x < _xAl; x++) {
    for (int y = 0; y < _yAl; y++) {
      if (_cells[x][y] == biker->getNumber()) {
        _cells[x][y] = EMPTY;
      }
    }
  }
}

// _____________________________________________________________________________
void Arena::clearArea(size_t x, size_t y) {
  for (int i = -2; i < 3; i++) {
    for (int j = -2; j < 3; j++) {
      // make sure values are within arena alignments
      if (i + x >= 0 & j + y >= 0 & i + x < _xAl & j + y < _yAl) {
        _cells[i + x][j + y] = EMPTY;
      }
    }
  }
}

// _____________________________________________________________________________
void Arena::reset() {
  for (int x = 0; x < _xAl; x++) {
    for (int y = 0; y < _yAl; y++) {
      _cells[x][y] = EMPTY;
    }
  }
}

// _____________________________________________________________________________
size_t Arena::getXAl() const {
  return _xAl;
}

// _____________________________________________________________________________
size_t Arena::getYAl() const {
  return _yAl;
}

// _____________________________________________________________________________
Arena::CellStatus Arena::getCellStatus(int x, int y) const {
  if (x < 0 | y < 0 | x >= _xAl | y >= _yAl) {
    return OUTSIDE;
  }
  return _cells[x][y];
}
