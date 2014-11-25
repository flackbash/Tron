// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>


#ifndef PROGRAMMING_ARMAGETRON_TRON_H_  // NOLINT
#define PROGRAMMING_ARMAGETRON_TRON_H_  // NOLINT

#include "./Biker.h"

// class for the game
class Tron {
 public:
  // constructor
  Tron();

  // destructor
  ~Tron();

  // add a computer opponent to the game
  Biker* createOpponent();

  // put different components of the game together to make it playable
  void play();

  // end the game in the appropriate way
  void endGame();

  // status of the game:
  enum GameStatus { ONGOING, LOST, WON };
  GameStatus getStatus() const;

 private:
  GameStatus _status;

  // number of computer opponents
  int _opponents;
};

#endif  // PROGRAMMING_ARMAGETRON_TRON_H_  // NOLINT
