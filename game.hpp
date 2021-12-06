#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "consts.hpp"
#include "piece.hpp"
#include <SFML/Graphics.hpp>

class game
{
private:
  board board;
  std::vector<std::unique_ptr<piece>> pieces;
  bool turn;      // true if red's turn, false if yellow's turn
  int turnNumber; // which turn we're on
  int winner;
  int selectedCol;
  bool started;
  bool gameType;         // true for 2p, false for 1p
  int generateBotMove(); // determines which column the bot should place a piece in
  int canWin(bool);      // given a bool representing the piece color, determines if that piece can win on the next move.
                         // returns the column in which to place the piece to win, if so
                         // returns -1 ow

public:
  game();
  virtual ~game();
  bool hasStarted();
  bool vsBot();
  void start(bool); // starts the game, true for 2p, false for 1p (vs bot)
  void addPiece();  // adds a piece to the board (based on user click or bot's generated position, depending on whose turn it is and 1p or 2p)
  bool isDone();
  void reset();
  void setSelectedCol(int);
  int getSelectedCol();
  void drawTo(sf::RenderWindow &, sf::Font &); // draws the game state to the passed in window
  void tick();
};
#endif // GAME_HPP