#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include <SFML/Graphics.hpp>

#define PADDING 20 // half the amount of space in between circles on the board
#define PIECE_RADIUS 50
#define WIDTH ((2 * PIECE_RADIUS * NUM_COLS) + (2 * NUM_COLS * PADDING))  // allows for evenly spaced circles across the board
#define HEIGHT ((2 * PIECE_RADIUS * NUM_ROWS) + (2 * NUM_ROWS * PADDING)) // allows for evenly spaced circles top to bottom

class game {
  private:
    board board;
    bool turn;      // true if red's turn, false if yellow's turn
    int turnNumber; // which turn we're on
    int winner;
    int selectedCol;

  public:
    game();
    virtual ~game();
    void addPiece();
    bool isDone();
    void reset();
    void setSelectedCol(int);
    void drawTo(sf::RenderWindow &, sf::Font &);
};

#endif // GAME_HPP