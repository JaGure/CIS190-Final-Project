#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>

class board
{
private:
    std::array<std::array<int>> board;

public:
    board();
    board(const board &);
    board(board &&);

    virtual ~board();

    void insert(int, int);
    bool checkForWin();
    void reset();
}

#endif