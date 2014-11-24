// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>

#include "./Biker.h"

// _____________________________________________________________________________
Biker::Biker(size_t x, size_t y, Direction direction, int number) {
  _xStartPos = x;
  _yStartPos = y;
  _xPos = _xStartPos;
  _yPos = _yStartPos;
  _direction = direction;
  _bikeNumber = number;
}

// _____________________________________________________________________________
Biker::~Biker() {}

// _____________________________________________________________________________
void Biker::move(Arena* arena) {
  size_t xOld = _xPos;
  size_t yOld = _yPos;
  switch (_direction) {
    case UP:
      _yPos++;
      break;
    case DOWN:
      _yPos--;
      break;
    case RIGHT:
      _xPos++;
      break;
    case LEFT:
      _xPos--;
      break;
  }
  if (crashControl(_xPos, _yPos, arena) == true) {
    printf("\x1b[%d;%dHCrash! Direction: %d\n", 20, 20, _direction);
    crashHandling(arena);
    // TODO(flackbash): remove - just for debugging purposes:
    _xPos = xOld;
    _yPos = yOld;
  } else {
    arena->addWall(this);
  }
}

// _____________________________________________________________________________
void Biker::turn(Direction direction) {
  switch (direction) {
    case UP:
      _direction = UP;
      break;
    case DOWN:
      _direction = DOWN;
      break;
    case RIGHT:
      _direction = RIGHT;
      break;
    case LEFT:
      _direction = LEFT;
      break;
  }
}

// _____________________________________________________________________________
bool Biker::crashControl(size_t x, size_t y, Arena* arena) {
  // no crash if cell status is EMPTY
  if (arena->getCellStatus(x, y) == 0) {
    return false;
  } else {
    return true;
  }
}

// _____________________________________________________________________________
void Biker::crashHandling(Arena* arena) {
  arena->removeWall(this);
}

// _____________________________________________________________________________
size_t Biker::getXPos() const {
  return _xPos;
}

// _____________________________________________________________________________
size_t Biker::getYPos() const {
  return _yPos;
}

// _____________________________________________________________________________
Biker::Direction Biker::getDirection() const {
  return _direction;
}

// _____________________________________________________________________________
int Biker::getNumber() const {
  return _bikeNumber;
}

// _____________________________________________________________________________
void Computer::getRandomMove() {}

// _____________________________________________________________________________
Player::Player(size_t x, size_t y, Direction direction, int number)
: Biker(x, y, direction, number) {}
