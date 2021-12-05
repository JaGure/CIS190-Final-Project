#include <SFML/Graphics.hpp>

#include "board.hpp"
#include <iostream>

int main() {
    // set up constants for drawing
    const auto numCols{7};
    const auto numRows{6};
    const auto padding{20}; // half the amount of space in between circles on the board
    const auto pieceRadius{50};
    const auto width{(2 * pieceRadius * numCols) + (2 * numCols * padding)};  // allows for evenly spaced circles across the board
    const auto height{(2 * pieceRadius * numRows) + (2 * numRows * padding)}; // allows for evenly spaced circles top to bottom

    // for keeping track of where the mouse is on the screen (which column)
    auto mouseCol{0};

    int winner{0};

    sf::Font font;
    if (!font.loadFromFile("coolvetica rg.otf")) {
        std::cerr << "Could not load font"
                  << "\n";
        exit(1);
    }

    board board{};

    // open the window
    sf::RenderWindow window(sf::VideoMode(width, height), "Connect 4!");

    // run the program as long as the window is open
    while (window.isOpen()) {
        /*
         * event handling
         */
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                mouseCol = event.mouseMove.x * numCols / width;
                break;
            case sf::Event::MouseButtonPressed:
                // place piece on left click (if game not over)
                if (event.mouseButton.button == sf::Mouse::Left && winner == 0) {
                    board.insert(mouseCol);

                    // check if the user has won after placing a piece
                    winner = board.checkForWin();
                    switch (winner) {
                    case 1:
                        std::cout << "red wins!\n";
                        break;
                    case -1:
                        std::cout << "yellow wins!\n";
                        break;
                    default:
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }

        /*
         * drawing
         */
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

                sf::CircleShape piece(pieceRadius);
                piece.setPosition(padding + (rowPos * 2 * pieceRadius) + (rowPos * padding * 2),
                                  padding + (colPos * 2 * pieceRadius) + (colPos * padding * 2));

                if (*rowStart == 1) {
                    piece.setFillColor(sf::Color::Red);
                } else if (*rowStart == -1) {
                    piece.setFillColor(sf::Color::Yellow);
                } else {
                    piece.setFillColor(sf::Color::Black);
                }

                window.draw(piece);

                rowStart++;
            }

            colStart++;
        }

        // draw the victory message
        if (winner != 0) {
            sf::RectangleShape winBox(sf::Vector2f(width * 2 / 3, height * 1 / 3));
            winBox.setPosition(width / 6, height / 3);
            winBox.setFillColor(sf::Color::Black);

            sf::Text winText;
            winText.setFont(font);

            std::string winMessage = (winner == 1 ? "Red" : "Yellow");
            winMessage += " wins!";
            winText.setString(winMessage);
            winText.setCharacterSize(height / 7);
            winText.setFillColor(winner == 1 ? sf::Color::Red : sf::Color::Yellow);

            // center the win message
            sf::FloatRect winTextBounds = winText.getLocalBounds();
            winText.setOrigin(winTextBounds.left + winTextBounds.width / 2.f,
                              winTextBounds.top + winTextBounds.height / 2.f);
            winText.setPosition(sf::Vector2f(width / 2, height / 2));

            window.draw(winBox);
            window.draw(winText);
        }

        // end the current frame
        window.display();
    }

    return 0;
}