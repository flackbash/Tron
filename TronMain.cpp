// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>

#include <iostream>
#include "./Tron.h"
#include "./Arena.h"
#include "./Biker.h"

// Main function.
int main(int argc, char** argv) {
  int xAl = 40;
  int yAl = 40;
  int numOpponents = 3;
  // TODO(flackbash): fix problem with non integer inputs
  while ( true ) {
    std::cout << "Arena width (type 0 for default value): ";
    std::cin >> xAl;
    if (xAl > 9 & xAl < 100 | xAl == 0) {
      break;
    }
    std::cout << "Must be a number between 10 and 99. Try again.";
  }
  while ( true ) {
    std::cout << "Arena heigth (type 0 for default value): ";
    std::cin >> yAl;
    if (yAl > 9 & yAl < 50 | yAl == 0) {
      break;
    }
    std::cout << "Must be a number between 10 and 49. Try again.";
  }
  while ( true ) {
    std::cout << "Number of opponents: ";
    std::cin >> numOpponents;
    if (numOpponents > 0 & numOpponents < 6) {
      break;
    }
    std::cout << "Must be a number between 0 and 5. Try again.";
  }
  Tron tron(xAl, yAl, numOpponents);
  tron.play();
}
