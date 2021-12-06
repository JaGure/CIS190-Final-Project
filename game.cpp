#include "game.hpp"
#include <array>
#include <iostream>
game::game() : board(), turn{true}, turnNumber{1}, winner{0}, selectedCol{-1}, started{false} {}

game::~game() {}

bool game::hasStarted() {
    return started;
}

void game::start(bool gameType) {
    started = true;
    this->gameType = gameType;
}

// in a two player game, just adds the piece in the selected column
// in a one player game, adds the piece in the selected column, followed by a bot piece
void game::addPiece() {
    board.insert(selectedCol, turn);
    pieces.push_back(std::make_unique<piece>(turn, PADDING + (selectedCol * 2 * PIECE_RADIUS) + (selectedCol * PADDING * 2)));
    for (std::unique_ptr<piece> &piece_ptr : pieces) {
        std::cout << piece_ptr.get() << " pos: " << piece_ptr->getPosition().x << " " << piece_ptr->getPosition().y << ", ";
    }
    std::cout << std::endl;

    turn = !turn;
    turnNumber++;
    winner = board.checkForWin();

    // also add the bot piece (if 1p and if the above did not end the game)
    if (!gameType && winner == 0) {
        board.insert(generateBotMove(), turn);
        turn = !turn;
        turnNumber++;
        winner = board.checkForWin();
    }
}

int game::generateBotMove() {
    auto gameBoard{board.getBoard()};

    // Prevent red from winning
    auto redWin{canWin(true)};
    if (redWin != -1)
        return redWin;

    // Try to win
    auto yellowWin{canWin(false)};
    if (yellowWin != -1)
        return yellowWin;

    // if can't win, figure out where can play
    std::array<int, NUM_COLS>
        topsOfColumns{};
    for (auto i{0}; i < NUM_COLS; i++) {
        topsOfColumns[i] = -1;
    }

    for (auto i{0}; i < NUM_COLS; i++) {
        for (auto j{NUM_ROWS - 1}; j >= 0; j--) {
            if (gameBoard[j][i] == 0 && topsOfColumns[i] == -1) {
                topsOfColumns[i] = j;
            }
        }
    }

    // try and play as close to as many other reds as possible
    std::array<int, NUM_COLS> numReds{};
    for (auto i{0}; i < NUM_COLS; i++) {
        auto colTop{topsOfColumns[i]};
        numReds[i] = 0;

        // to the left of the piece
        if (i > 0) {
            // top left
            if (colTop > 0 && gameBoard[colTop - 1][i - 1] == 1)
                numReds[i]++;

            // left
            if (gameBoard[colTop][i - 1] == 1)
                numReds[i]++;

            // bottom left
            if (colTop < NUM_ROWS - 1 && gameBoard[colTop + 1][i - 1] == 1)
                numReds[i]++;
        }

        // below
        if (colTop < NUM_ROWS - 1 && gameBoard[colTop + 1][i] == 1)
            numReds[i]++;

        // to the right
        if (i < NUM_COLS - 1) {
            // top right
            if (colTop > 0 && gameBoard[colTop - 1][i + 1] == 1)
                numReds[i]++;

            // right
            if (gameBoard[colTop][i + 1] == 1)
                numReds[i]++;

            // bottom right
            if (colTop < NUM_ROWS - 1 && gameBoard[colTop + 1][i + 1] == 1)
                numReds[i]++;
        }
    }

    int max{numReds[0]};
    int maxPos{0};

    for (auto i{0}; i < NUM_COLS; i++) {
        if (numReds[i] > max) {
            max = numReds[i];
            maxPos = i;
        }
    }

    return maxPos;
}

int game::canWin(bool piece) {
    auto gameBoard{board.getBoard()};
    int consecutive{0};
    auto color{piece ? 1 : -1};

    // check close to row win
    for (int row{0}; row < NUM_ROWS; row++) {
        for (int col{0}; col < NUM_COLS; col++) {
            if (gameBoard[row][col] != color) {
                consecutive = 0;
            } else {
                consecutive++;
                if (consecutive == 3) {
                    // if can place piece to left of row
                    if (col > 2 && gameBoard[row][col - 3] == 0 && (row == NUM_ROWS - 1 || gameBoard[row + 1][col - 3] != 0))
                        return col - 3;

                    // if can place piece to right of row
                    if (col < NUM_COLS - 1 && gameBoard[row][col + 1] == 0 && (row == NUM_ROWS - 1 || gameBoard[row + 1][col + 1] != 0))
                        return col + 1;
                }
            }
        }
    }

    consecutive = 0;

    // check for close to column win
    for (int col{0}; col < NUM_COLS; col++) {
        for (int row{0}; row < NUM_ROWS; row++) {
            if (gameBoard[row][col] != color) {
                consecutive = 0;
            } else {
                consecutive++;
                // if can place piece on top of column
                if (consecutive == 3 && row > 2 && gameBoard[row - 3][col] == 0)
                    return col;
            }
        }
    }

    consecutive = 0;

    // check for close to diagonal win
    for (int row{0}; row < NUM_ROWS; row++) {
        for (int col{0}; col < NUM_COLS; col++) {
            if (gameBoard[row][col] != color)
                continue;

            // down
            consecutive = 1;
            int i{row + 1};
            int j{col + 1};
            while (i < NUM_ROWS && j < NUM_COLS && gameBoard[i++][j++] == color) {
                if (++consecutive == 3) {
                    // check if can place bottom right
                    if (j < NUM_COLS && i < NUM_ROWS && gameBoard[i][j] == 0 && (i == NUM_ROWS - 1 || gameBoard[i + 1][j] != 0))
                        return j;

                    // check if can place top left
                    int potentialJ{j - 4};
                    int potentialI{i - 4};
                    if (potentialJ >= 0 && potentialI >= 0 && gameBoard[potentialI][potentialJ] == 0 && gameBoard[potentialI + 1][potentialJ] != 0)
                        return potentialJ;
                }
            }
            // up
            consecutive = 1;
            i = row + 1;
            j = col - 1;
            while (i < NUM_ROWS && j >= 0 && gameBoard[i++][j--] == color) {
                if (++consecutive == 3) {
                    // check if can place bottom left
                    if (j >= 0 && i < NUM_ROWS && gameBoard[i][j] == 0 && (i == NUM_ROWS - 1 || gameBoard[i + 1][j] != 0))
                        return j;

                    // check if can place top right
                    int potentialJ{j + 4};
                    int potentialI{i - 4};
                    if (potentialJ < NUM_COLS && potentialI >= 0 && gameBoard[potentialI][potentialJ] == 0 && gameBoard[potentialI + 1][potentialJ] != 0)
                        return potentialJ;
                }
            }
        }
    }

    return -1;
}

bool game::isDone() {
    return turnNumber == 43 || winner != 0;
}

void game::reset() {
    board.clear();
    turn = true;
    turnNumber = 1;
    winner = 0;
    selectedCol = -1;
    started = false;
    pieces.clear();
}

void game::setSelectedCol(int selectedCol) {
    this->selectedCol = selectedCol;
}

void game::tick() {
    for (std::unique_ptr<piece> &piece_ptr : pieces) {
        piece_ptr->updatePhysics(pieces);
    }
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

            piece.setFillColor((!isDone() && rowPos == selectedCol) ? sf::Color::Green : sf::Color::Black);
            window.draw(piece);

            rowStart++;
        }

        colStart++;
    }

    // draw the start message
    if (!started) {
        sf::RectangleShape messageBox(sf::Vector2f(WIDTH * 2 / 3, HEIGHT * 2 / 3));
        messageBox.setPosition(WIDTH / 6, HEIGHT / 6);
        messageBox.setFillColor(sf::Color::Black);

        sf::Text startHeader;
        startHeader.setFont(font);
        startHeader.setString("Connect 4");
        startHeader.setCharacterSize(HEIGHT / NUM_COLS);
        startHeader.setFillColor(sf::Color::Blue);

        sf::Text message;
        message.setFont(font);
        message.setString("Press 1 for 1P, 2 for 2P");
        message.setCharacterSize(HEIGHT / NUM_COLS / 2);
        message.setFillColor(sf::Color::Blue);

        // center the messages
        sf::FloatRect headerBounds = startHeader.getLocalBounds();
        startHeader.setOrigin(headerBounds.left + headerBounds.width / 2.f,
                              headerBounds.top + headerBounds.height / 2.f);
        startHeader.setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2 - HEIGHT / 6));

        sf::FloatRect messageBounds = message.getLocalBounds();
        message.setOrigin(messageBounds.left + messageBounds.width / 2.f,
                          messageBounds.top + messageBounds.height / 2.f);
        message.setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2 + HEIGHT / 6));

        window.draw(messageBox);
        window.draw(startHeader);
        window.draw(message);
    }

    for (std::unique_ptr<piece> &piece_ptr : pieces) {
        piece_ptr->drawTo(window, font);
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