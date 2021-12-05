#include "game.hpp"

game::game() : board(), turn{true}, turnNumber{1}, winner{0}, selectedCol{-1} {}

game::~game() {}

void game::addPiece() {
    board.insert(selectedCol, turn);
    turn = !turn;
    turnNumber++;
    winner = board.checkForWin();
}

bool game::isDone() {
    return turnNumber == 43 || winner != 0;
}

void game::reset() {
    board.clear();
    turn = true;
    turnNumber = 1;
}

void game::setSelectedCol(int selectedCol) {
    this->selectedCol = selectedCol;
}

void game::drawTo(sf::RenderWindow &window, sf::Font &font) {
    // clear the window with blue color
    window.clear(sf::Color::Blue);

    // draw the board
    auto gameBoard{board.getBoard()};

    auto colStart{gameBoard.begin()};
    auto colEnd{gameBoard.end()};
    while (colStart < colEnd) {
        auto rowStart{(*colStart).begin()};
        auto rowEnd{(*colStart).end()};

        while (rowStart < rowEnd) {
            auto colPos{colStart - gameBoard.begin()};
            auto rowPos{rowStart - (*colStart).begin()};

            sf::CircleShape piece(PIECE_RADIUS);
            piece.setPosition(PADDING + (rowPos * 2 * PIECE_RADIUS) + (rowPos * PADDING * 2),
                              PADDING + (colPos * 2 * PIECE_RADIUS) + (colPos * PADDING * 2));

            if (*rowStart == 1) {
                piece.setFillColor(sf::Color::Red);
            } else if (*rowStart == -1) {
                piece.setFillColor(sf::Color::Yellow);
            } else {
                piece.setFillColor((!isDone() && rowPos == selectedCol) ? sf::Color::Green : sf::Color::Black);
            }

            window.draw(piece);

            rowStart++;
        }

        colStart++;
    }

    // draw the victory/end message
    if (isDone()) {
        sf::RectangleShape winBox(sf::Vector2f(WIDTH * 2 / 3, HEIGHT * 1 / 3));
        winBox.setPosition(WIDTH / NUM_ROWS, HEIGHT / 3);
        winBox.setFillColor(sf::Color::Black);

        sf::Text winText;
        winText.setFont(font);

        std::string winMessage;
        if (winner == 1) {
            winMessage = "Red wins!";
        } else if (winner == -1) {
            winMessage = "Yellow wins!";
        } else {
            winMessage = "Draw.";
        }

        winText.setString(winMessage);
        winText.setCharacterSize(HEIGHT / NUM_COLS);
        winText.setFillColor(winner == 1 ? sf::Color::Red : sf::Color::Yellow);

        // center the win message
        sf::FloatRect winTextBounds = winText.getLocalBounds();
        winText.setOrigin(winTextBounds.left + winTextBounds.width / 2.f,
                          winTextBounds.top + winTextBounds.height / 2.f);
        winText.setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2));

        window.draw(winBox);
        window.draw(winText);
    }
}