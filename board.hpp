#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>

// header for 7 col x 6 row board
class board
{
private:
    std::array<std::array<int, 7>, 6> gameBoard; // 2D array of 1s,0s, & -1s. 1 = red piece, 0 = no piece, -1 = yellow piece

public:
    board();

    virtual ~board();

    std::array<std::array<int, 7>, 6> getBoard();
    void insert(bool, int);
    bool checkForWin();
};

#endif