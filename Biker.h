// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>


#ifndef PROGRAMMING_ARMAGETRON_BIKER_H_  // NOLINT
#define PROGRAMMING_ARMAGETRON_BIKER_H_  // NOLINT

#include <stdio.h>
#include <gtest/gtest.h>
#include "./Arena.h"

// abstract class for the biker
class Biker {
 public:
  enum Direction {
    UP = 65, DOWN = 66, RIGHT = 67, LEFT = 68
  };

  // constructor
  Biker(size_t x, size_t y, Direction direction, int number);

  // destructor
  ~Biker();

  // take an input and execute the corresponding move
  void move(Arena* arena);
  FRIEND_TEST(TronTest, move);

  // change the direction according to given parameter
  void turn(Direction direction);

  // check whether there was a crash
  bool crashControl(size_t x, size_t y, Arena* arena);

  // take appropriate action when a crash was detected
  void crashHandling(Arena* arena);

  // get current x coordinate of the biker
  size_t getXPos() const;

  // get current y coordinate of the biker
  size_t getYPos() const;

  // get current direction of the biker
  Direction getDirection() const;

  // get number of the biker
  int getNumber() const;

 private:
  // number of the biker
  int _bikeNumber;

  // current x coordinate of the biker
  int _xPos;

  // current y coordinate of the biker
  int _yPos;

  // current direction of the biker
  Direction _direction;

  // start x coordinate of the biker
  size_t _xStartPos;

  // start y coordinate of the biker
  size_t _yStartPos;
};

// class for a computer biker
class Computer : public Biker {
 public:
  // constructor
  Computer(size_t x, size_t y, Direction direction, int number);

  // destructor
  ~Computer();

  // create a random move
  void getRandomMove();
};

// class for a player
class Player : public Biker {
 public:
  // constructor
  Player(size_t x, size_t y, Direction direction, int number);

  // destructor
  ~Player();
};

#endif  // PROGRAMMING_ARMAGETRON_BIKER_H_  // NOLINT
