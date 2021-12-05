#include "board.hpp"
#include <array>

board::board() : gameBoard{{{0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0}}} {
}

board::~board() {
}

std::array<std::array<int, 7>, 6> board::getBoard() {
    return gameBoard;
}

// insert the specificed piece into the specified column
// true inserts a red piece, false inserts a yellow piece
void board::insert(int col) {
    auto colStart{gameBoard.begin()};
    auto colEnd{gameBoard.end() - 1};

    // iterate backwards so that we can insert the piece as low as possible
    while (colEnd >= colStart) {
        auto rowStart{(*colEnd).begin()};
        auto rowEnd{(*colEnd).end()};

        // get the rowStart pointer to the input column
        while (rowStart < rowEnd && rowStart - ((*colEnd).begin()) != col) {
            rowStart++;
        }

        // some problem in input column
        if (rowStart == rowEnd) {
            return;
        }

        // found the column, check if we can insert, insert if so
        // otherwise, go to the next row up
        if (*rowStart == 0) {
            if (turn) {
                *rowStart = 1;
            } else {
                *rowStart = -1;
            }
            turn = !turn;
            return;
        }

        colEnd--;
    }
}

// checks if a player has won
// returns 1 if red has one, -1 if yellow has won, 0 otherwise
int board::checkForWin() {
    int color = 0;
    int consecutive = 0;

    // row win
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            if (gameBoard[row][col] == 0) {
                consecutive = 0;
            } else {
                consecutive = gameBoard[row][col] == color ? consecutive + 1 : 1;
                color = gameBoard[row][col];
                if (consecutive == 4) return color;
            }
        }
    }

    color = 0;
    consecutive = 0;

    // column win
    for (int col = 0; col < 7; col++) {
        for (int row = 0; row < 6; row++) {
            if (gameBoard[row][col] == 0) {
                consecutive = 0;
            } else {
                consecutive = gameBoard[row][col] == color ? consecutive + 1 : 1;
                color = gameBoard[row][col];
                if (consecutive == 4) return color;
            }
        }
    }

    color = 0;
    consecutive = 0;

    // diagonal win
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            color = gameBoard[row][col];
            if (color == 0) continue;
            // down
            consecutive = 1;
            int i = row + 1;
            int j = col + 1;
            while (i < 6 && j < 7 && gameBoard[i++][j++] == color) {
                if (++consecutive == 4) return color;
            }
            // up
            consecutive = 1;
            i = row + 1;
            j = col - 1;
            while (i < 6 && j >= 0 && gameBoard[i++][j--] == color) {
                if (++consecutive == 4) return color;
            }
        }
    }

    return 0;
}