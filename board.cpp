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

// insert the specificed piece into the specified column
// true inserts a red piece, false inserts a yellow piece
void board::insert(int col)
{
    auto colStart{gameBoard.begin()};
    auto colEnd{gameBoard.end() - 1};

    // iterate backwards so that we can insert the piece as low as possible
    while (colEnd >= colStart)
    {
        auto rowStart{(*colEnd).begin()};
        auto rowEnd{(*colEnd).end()};

        // get the rowStart pointer to the input column
        while (rowStart < rowEnd && rowStart - ((*colEnd).begin()) != col)
        {
            rowStart++;
        }

        // some problem in input column
        if (rowStart == rowEnd)
        {
            return;
        }

        // found the column, check if we can insert, insert if so
        // otherwise, go to the next row up
        if (*rowStart == 0)
        {
            if (turn)
            {
                *rowStart = 1;
            }
            else
            {
                *rowStart = -1;
            }
            turn = !turn;
            return;
        }

        colEnd--;
    }
}