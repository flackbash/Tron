// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>

#include <gtest/gtest.h>
#include "./Tron.h"
#include "./Biker.h"
#include "./Arena.h"

// _____________________________________________________________________________
TEST(TronTest, move) {
  Arena* arena = new Arena(10, 10);
  Biker* biker = new Biker(5, 5, Biker::Direction::UP, 1);

  // tests without crash
  biker->_direction = Biker::Direction::DOWN;
  biker->move(arena);
  ASSERT_EQ(5, biker->_xPos);
  ASSERT_EQ(4, biker->_yPos);

  biker->_direction = Biker::Direction::LEFT;
  biker->move(arena);
  ASSERT_EQ(4, biker->_xPos);
  ASSERT_EQ(4, biker->_yPos);

  biker->_direction = Biker::Direction::UP;
  biker->move(arena);
  ASSERT_EQ(4, biker->_xPos);
  ASSERT_EQ(5, biker->_yPos);

  biker->_direction = Biker::Direction::RIGHT;
  biker->move(arena);
  ASSERT_EQ(5, biker->_xPos);
  ASSERT_EQ(5, biker->_yPos);
}

// _____________________________________________________________________________
TEST(TronTest, crashControl) {
  Arena* arena = new Arena(10, 10);
  Player* player = new Player(5, 5, Biker::Direction::UP, -1);

  for (int i = 0; i < arena->getXAl(); i++) {
    arena->_cells[i][3] = Arena::CellStatus::PLAYER1;
  }

  ASSERT_FALSE(player->crashControl(1, 5, arena));
  ASSERT_FALSE(player->crashControl(5, 5, arena));
  ASSERT_TRUE(player->crashControl(1, 3, arena));
  ASSERT_TRUE(player->crashControl(1, 12, arena));
}

// _____________________________________________________________________________
TEST(TronTest, getCellStatus) {
  Arena* arena = new Arena(10, 10);
  Player* player = new Player(5, 5, Biker::Direction::UP, -1);

  for (int i = 0; i < arena->getXAl(); i++) {
    arena->_cells[i][3] = Arena::CellStatus::PLAYER1;
  }

  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {
      if (y == 3) {
        ASSERT_EQ(-1, arena->getCellStatus(x, y));
      } else {
        ASSERT_EQ(0, arena->getCellStatus(x, y));
      }
    }
  }
  ASSERT_EQ(-10, arena->getCellStatus(-1, 2));
  ASSERT_EQ(-10, arena->getCellStatus(10, 2));
  ASSERT_EQ(-10, arena->getCellStatus(1, -1));
  ASSERT_EQ(-10, arena->getCellStatus(1, 10));
}

// _____________________________________________________________________________
TEST(TronTest, addWall) {
  Arena* arena = new Arena(10, 10);
  Player* player = new Player(5, 5, Biker::Direction::UP, -1);

  arena->addWall(player);
  ASSERT_EQ(-1, arena->getCellStatus(5, 5));
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {
      if (x != 5 | y != 5) {
        ASSERT_EQ(0, arena->getCellStatus(x, y));
      }
    }
  }

  player->move(arena);
  player->move(arena);
  ASSERT_EQ(-1, arena->getCellStatus(5, 5));
  ASSERT_EQ(-1, arena->getCellStatus(5, 6));
  ASSERT_EQ(-1, arena->getCellStatus(5, 7));
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {
      if (x != 5 | (y != 5 & y != 6 & y != 7)) {
        ASSERT_EQ(0, arena->getCellStatus(x, y));
      }
    }
  }
}

// _____________________________________________________________________________
TEST(TronTest, removeWall) {
  Arena* arena = new Arena(10, 10);
  Player* player = new Player(5, 5, Biker::Direction::UP, -1);

  for (int i = 0; i < arena->getXAl(); i++) {
    arena->_cells[i][3] = Arena::CellStatus::PLAYER1;
  }

  arena->removeWall(player);
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {
      ASSERT_EQ(0, arena->getCellStatus(x, y));
    }
  }
}
