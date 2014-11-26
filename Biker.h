// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>


#ifndef PROGRAMMING_ARMAGETRON_BIKER_H_  // NOLINT
#define PROGRAMMING_ARMAGETRON_BIKER_H_  // NOLINT

#include <stdio.h>
#include <gtest/gtest.h>
#include <vector>
#include "./Arena.h"

// class for a biker
class Biker {
 public:
  enum Direction {
    UP = 65, DOWN = 66, RIGHT = 67, LEFT = 68
  };

  // constructor
  Biker(size_t x, size_t y, Direction direction, int number);

  // get the new position of the biker assuming he is heading into <direction>
  std::vector<int> getNewPosition(Direction direction) const;

  // take an input and execute the corresponding move
  void move(Arena* arena);
  FRIEND_TEST(TronTest, move);

  // create a random move
  Direction getRandomDirection() const;

  // change the direction according to given parameter
  void turn(Direction direction);

  // check whether there has been a crash
  bool crashControl(size_t x, size_t y, Arena* arena) const;

  // take appropriate action when a crash was detected
  void crashHandling(Arena* arena);

  // reset the biker (affects position, direction, status)
  void reset();

  // get current x coordinate
  size_t getXPos() const;

  // get current y coordinate
  size_t getYPos() const;

  // get current direction
  Direction getDirection() const;

  // get bike number
  int getNumber() const;

  // get status
  enum Status {
    RACING = 1, DESTROYED = 0
  };
  Status getStatus() const;

 private:
  // bike number: player < 0, computer > 0
  int _bikeNumber;

  // current x coordinate
  int _xPos;

  // current y coordinate
  int _yPos;

  // start x coordinate
  int _startXPos;

  // start x coordinate
  int _startYPos;

  // current direction
  Direction _direction;

  // start direction
  Direction _startDirection;

  // status (RACING or DESTROYED)
  Status _status;
};

#endif  // PROGRAMMING_ARMAGETRON_BIKER_H_  // NOLINT
