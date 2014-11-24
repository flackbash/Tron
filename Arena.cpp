// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>

#include <stdio.h>
#include "./Arena.h"
#include "./Biker.h"

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
  printf("\x1b[31m");
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

  printf("\x1b[0m");
  // print the bikers' walls
  for (int y = 0; y < _yAl; y++) {
    for (int x = 0; x < _xAl; x++) {
      for (int s = 0; s < 2; s++) {
        if (_cells[x][y] != EMPTY) {
          printf("\x1b[7m");
        } else {
          printf("\x1b[0m");
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
void Arena::clearArea(size_t x, size_t y) {}

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
