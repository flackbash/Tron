// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>


#ifndef PROGRAMMING_ARMAGETRON_TRON_H_  // NOLINT
#define PROGRAMMING_ARMAGETRON_TRON_H_  // NOLINT

#include <vector>
#include "./Biker.h"

// class for the game
class Tron {
 public:
  // constructor
  Tron(int sizeX, int sizeY, int numOpponents, int speed);

  // destructor
  ~Tron();

  // add <number> computer opponents to the game
  void addOpponents(int number);

  // put different components of the game together to make it playable
  void play();

  // end the game in an appropriate way
  void endGame();

  // reset values for replay
  void reset();

  // get the status of the game
  enum GameStatus { ONGOING, LOST, WON };
  GameStatus getStatus() const;

 private:
  // status of the game
  GameStatus _status;

  // number of computer opponents
  int _numOpponents;

  // speed of the game ranging from 1 to 40 with 40 being the fastest speed
  int _speed;

  // vector that holds all involved computer opponents
  std::vector<Biker*> _opponents;

  // player (initialized in the constructor since it is essential for the game)
  Biker* player;

  // arena (initialized in the constructor since it is essential for the game)
  Arena* arena;
};

#endif  // PROGRAMMING_ARMAGETRON_TRON_H_  // NOLINT
