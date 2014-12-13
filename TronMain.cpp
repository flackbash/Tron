// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>

/*
* Ideas:
* further improvement on speed consistency
* make computer opponents more intelligent
*   computer opponents try to move within a certain radius of the player
*   computer opponents try to move straight for a longer periode of time
*/

#include <iostream>
#include "./Tron.h"
#include "./Arena.h"
#include "./Biker.h"

// Main function.
int main(int argc, char** argv) {
  int xAl = 0;
  int yAl = 0;
  int numPlayers = 1;
  int numOpponents = 5;
  int speed = 4;
  char def;
  // TODO(flackbash): fix problem with non integer inputs
  std::cout << "Default values? (y[es] / any other key) ";
  std::cin >> def;
  if (def != 'y') {
    while ( true ) {
      std::cout << "Arena width (default = 0): ";
      std::cin >> xAl;
      if (xAl > 9 & xAl < 100 | xAl == 0) {
        break;
      }
      std::cout << "Must be a number between 10 and 99. Try again.";
    }
    while ( true ) {
      std::cout << "Arena heigth (default = 0): ";
      std::cin >> yAl;
      if (yAl > 9 & yAl < 50 | yAl == 0) {
        break;
      }
      std::cout << "Must be a number between 10 and 49. Try again.";
    }
    while ( true ) {
      std::cout << "Number of players: ";
      std::cin >> numPlayers;
      if (numPlayers > 0 & numPlayers < 5) {
        break;
      }
      std::cout << "Must be a number between 1 and 4. Try again.";
    }
    while ( true ) {
      std::cout << "Number of opponents: ";
      std::cin >> numOpponents;
      if (numOpponents >= 0 & numOpponents < 6) {
        break;
      }
      std::cout << "Must be a number between 0 and 5. Try again.";
    }
    while ( true ) {
      std::cout << "Speed (1 fastest - 40 slowest): ";
      std::cin >> speed;
      if (speed > 0 & speed < 40) {
        break;
      }
      std::cout << "Must be a number between 1 and 39. Try again.";
    }
  }
  Tron tron(xAl, yAl, numPlayers, numOpponents, speed);
  tron.play();
}
