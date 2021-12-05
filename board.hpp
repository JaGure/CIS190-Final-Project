#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>

#define NUM_COLS 7
#define NUM_ROWS 6

class board
{
private:
    std::array<std::array<int, NUM_COLS>, NUM_ROWS> gameBoard; // 2D array of 1s,0s, & -1s. 1 = red piece, 0 = no piece, -1 = yellow piece

public:
    board();

    virtual ~board();

    std::array<std::array<int, NUM_COLS>, NUM_ROWS> getBoard();
    void insert(int, bool);
    void clear();
    int checkForWin();
};

#endif