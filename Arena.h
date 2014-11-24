// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>


#ifndef PROGRAMMING_ARMAGETRON_ARENA_H_  // NOLINT
#define PROGRAMMING_ARMAGETRON_ARENA_H_  // NOLINT

#include <stdio.h>
#include <gtest/gtest.h>

class Biker;

// class for the arena
class Arena {
 public:
  // constructor
  Arena(size_t x, size_t y);

  // destructor
  ~Arena();

  // display the arena
  void show();

  // add a new part of wall to the arena
  void addWall(Biker* biker);

  // remove the walls of the player that has just crashed
  void removeWall(Biker* biker);

  // delete  the walls in the direct surrounding of an explosion
  void clearArea(size_t x, size_t y);

  // get the x-alignment of the arena
  size_t getXAl() const;

  // get the y-alignment of the arena
  size_t getYAl() const;

  // check if and by whom a cell is occupied
  enum CellStatus {
    EMPTY = 0, PLAYER1 = -1, COMPUTER1 = 1, COMPUTER2 = 2,
    COMPUTER3 = 3, COMPUTER4 = 4, COMPUTER5 = 5, COMPUTER6 = 6, OUTSIDE = -10
  };
  CellStatus getCellStatus(int x, int y) const;
  FRIEND_TEST(TronTest, getCellStatus);
  FRIEND_TEST(TronTest, crashControl);
  FRIEND_TEST(TronTest, removeWall);

 private:
  // x and y alignment of the arena
  size_t _xAl;
  size_t _yAl;

  // holds which cells are occupied by which player and which are empty
  CellStatus** _cells;
};

#endif  // PROGRAMMING_ARMAGETRON_ARENA_H_  // NOLINT
