// Copyright 2014, flackbash
// Author: flackbash <flack2bash@gmail.com>

#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include "./Tron.h"
#include "./Biker.h"
#include "./Arena.h"

// _____________________________________________________________________________
Tron::Tron(int sizeX, int sizeY, int numPlayers, int numOpponents, int speed) {
  // initialize screen
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);

  _status = ONGOING;
  _numPlayers = numPlayers;
  _numOpponents = numOpponents;
  _speed = speed;

  // get window size and adjust arena size if the default value was demanded
  int winWidth, winHeight;
  getmaxyx(stdscr, winHeight, winWidth);
  if (sizeX == 0) {
    sizeX = (winWidth / 2) - 1;
  }
  if (sizeY == 0) {
    sizeY = winHeight - 2;
  }

  arena = new Arena(sizeX, sizeY);
}

// _____________________________________________________________________________
Tron::~Tron() {
  // "delete arena" conflicts with destructor of arena?
  endwin();
  for (auto& player : _players) {
    delete player;
  }
  for (auto& computer : _opponents) {
    delete computer;
  }
}

// _____________________________________________________________________________
void Tron::addBikers() {
  int pos;
  int startX;
  int startY;
  Biker::Direction startDirection;

  // possible start values: [x, y, direction, alreadyUsed]
  double start[9][4] = {
    {2, 1, 65, 0}, {3, 4, 66, 0}, {1, 3, 67, 0},
    {4, 2, 68, 0}, {4, 3, 68, 0}, {1, 2, 67, 0},
    {2, 4, 66, 0}, {3, 1, 65, 0}, {2.5, 2.5, 66, 0}
  };
  int xAl = arena->getXAl();
  int yAl = arena->getYAl();

  for (int i = -_numPlayers; i < _numOpponents; i++) {
    // get a random position
    unsigned int seed = (unsigned int)(time(NULL));
    pos = rand_r(&seed) % (_numPlayers + _numOpponents);
    while (start[pos][3] == 1) {
      pos = (pos + 1) % (_numPlayers + _numOpponents);
    }
    start[pos][3] = 1;
    startX = (xAl / 5) * start[pos][0];
    startY = (yAl / 5) * start[pos][1];
    startDirection = Biker::Direction(start[pos][2]);
    if (i < 0) {
      Biker* player = new Biker(startX, startY, startDirection, i);
      _players.push_back(player);
    } else {
      Biker* computer = new Biker(startX, startY, startDirection, i + 1);
      _opponents.push_back(computer);
    }
  }
}

// _____________________________________________________________________________
void Tron::play() {
  addBikers();

  // counter for moving into the current direction without a user input
  int counter = 0;

  while (true) {
    // get user input
    if (_status == ONGOING) {
      int key = getch();
      // turn the corresponding player according to the key
      for (auto& player : _players) {
        int number = player->getNumber();
        switch (number) {
          // player 1 moves by using "LEFT-ARROW" and "RIGHT-ARROW"
          case(-1):
            if (key == 67 | key == 68) player->turn(Biker::Direction(key));
            break;
          // player 2 moves by using "a" and "d"
          case(-2):
            if (key == 97) player->turn(Biker::Direction::LEFT);
            if (key == 100) player->turn(Biker::Direction::RIGHT);
            break;
          // player 3 moves by using "v" and "n"
          case(-3):
            if (key == 118) player->turn(Biker::Direction::LEFT);
            if (key == 110) player->turn(Biker::Direction::RIGHT);
            break;
          // player 4 moves by using "i" and "p"
          case(-4):
            if (key == 105) player->turn(Biker::Direction::LEFT);
            if (key == 112) player->turn(Biker::Direction::RIGHT);
            break;
        }
      }

      if (++counter % (10 * _speed) == 0) {
        // move computer opponents and get number of remaining opponents
        int oppLeft = 0;
        for (auto& computer : _opponents) {
          if (computer->getStatus() == Biker::Status::RACING) {
            computer->turnComputer(computer->getRandomDirection());
            computer->move(arena);
            oppLeft++;
          }
        }

        // move players and get number of remaining players
        int playersLeft = 0;
        for (auto& player : _players) {
          if (player->getStatus() == Biker::Status::RACING) {
            player->move(arena);
            playersLeft++;
          }
        }
        arena->printBorders();

        // check whether the game is lost (no player remaining)
        if (playersLeft == 0) {
          _status = LOST;
          endGame();
        // check whether the game is won (only one player remaining)
        } else {
          if (oppLeft == 0 & playersLeft == 1) {
            _status = WON;
            endGame();
          }
        }
      }
    } else {
      int ch = getch();
      if (ch == 'q') break;
      if (ch == 'r') reset();
    }
    usleep(1000);
  }
}

// _____________________________________________________________________________
void Tron::endGame() {
  // TODO(flackbash): adjust "won"-message to the player who is left
  int y = arena->getYAl();
  int x = arena->getXAl();

  printf("\x1b[0m");

  if (_status == LOST) {
    printf("\x1b[%d;%dHYOU LOST!\n", (y / 2) - 5, x - 4);
  } else if (_status == WON) {
    printf("\x1b[%d;%dHYOU WON!\n", (y / 2) - 5, x - 3);
  }

  printf("\x1b[%d;%dHPress 'Q' to quit.", (y / 2) - 3, x - 8);
  printf("\x1b[%d;%dHPress 'R' to play again.", (y / 2) - 2, x - 11);
  fflush(stdout);
}

// _____________________________________________________________________________
void Tron::reset() {
  clear();
  for (auto& player : _players) {
    player->reset();
  }
  for (auto& opponent : _opponents) {
    opponent->reset();
  }
  arena->reset();
  _status = ONGOING;
}

// _____________________________________________________________________________
Tron::GameStatus Tron::getStatus() const {
  return _status;
}
