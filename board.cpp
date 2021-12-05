#include "board.hpp"
#include <array>

board::board() : gameBoard{{{0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0}}}
{
}

board::~board()
{
}

std::array<std::array<int, 7>, 6> board::getBoard()
{
    return gameBoard;
}