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
Arena::Arena(int x, int y) {
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
  for (int i = 0; i < _xAl; i++) delete _cells[i];
  delete[] _cells;
}

// _____________________________________________________________________________
void Arena::printBorders() {
  printf("\x1b[7m");
  printf("%s", RED);
  // print horizontal borders
  for (int i = 1; i <= (_xAl * 2) + 2; i++) {
    printf("\x1b[%d;%dH ", 0, i);
    printf("\x1b[%d;%dH ", _yAl + 2, i);
  }
  // print vertical borders
  for (int i = 1; i <= _yAl + 1; i++) {
    printf("\x1b[%d;%dH ", i, 1);
    printf("\x1b[%d;%dH ", i, (_xAl * 2) + 2);
  }
  fflush(stdout);
}

// _____________________________________________________________________________
void Arena::printCell(int x, int y) {
  printf("\x1b[7m");
  for (int s = 0; s < 2; s++) {
    switch (_cells[x][y]) {
      case(EMPTY):
        printf("%s", RESET);
        break;
      case(PLAYER1):
        printf("%s", GREEN);
        break;
      case(PLAYER2):
        printf("%s", BLUE);
        break;
      case(PLAYER3):
        printf("%s", YELLOW);
        break;
      case(PLAYER4):
        printf("%s", RED);
        break;
      case(COMPUTER1):
        printf("%s", CYAN);
        break;
      case(COMPUTER2):
        printf("%s", MAGENTA);
        break;
      case(COMPUTER3):
        printf("%s", WHITE);
        break;
      case(COMPUTER4):
        printf("%s", CYAN);
        break;
      case(COMPUTER5):
        printf("%s", MAGENTA);
        break;
    }
    if (_cells[x][y] == EMPTY) printf("%s", RESET);
    printf("\x1b[%d;%dH ", (_yAl - y) + 1, (x * 2) + 2 + s);
  }
  fflush(stdout);
}

// _____________________________________________________________________________
void Arena::addWall(Biker* biker) {
  int x = biker->getXPos();
  int y = biker->getYPos();
  _cells[x][y] = CellStatus(biker->getNumber());
  printCell(x, y);
}

// _____________________________________________________________________________
void Arena::removeWall(Biker* biker) {
  for (int x = 0; x < _xAl; x++) {
    for (int y = 0; y < _yAl; y++) {
      if (_cells[x][y] == biker->getNumber()) {
        _cells[x][y] = EMPTY;
        printCell(x, y);
      }
    }
  }
}

// _____________________________________________________________________________
void Arena::clearArea(int x, int y) {
  for (int i = -2; i < 3; i++) {
    for (int j = -2; j < 3; j++) {
      // make sure values are within arena borders
      if (i + x >= 0 & j + y >= 0 & i + x < _xAl & j + y < _yAl) {
        _cells[i + x][j + y] = EMPTY;
        printCell(i + x, j + y);
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
int Arena::getXAl() const {
  return _xAl;
}

// _____________________________________________________________________________
int Arena::getYAl() const {
  return _yAl;
}

// _____________________________________________________________________________
Arena::CellStatus Arena::getCellStatus(int x, int y) const {
  if (x < 0 | y < 0 | x >= _xAl | y >= _yAl) {
    return OUTSIDE;
  }
  return _cells[x][y];
}
