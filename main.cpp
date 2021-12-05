#include <SFML/Graphics.hpp>

#include "board.hpp"
#include <iostream>

int main()
{
    // set up constants for drawing
    const auto numCols{7};
    const auto numRows{6};
    const auto padding{20}; // half the amount of space in between circles on the board
    const auto pieceRadius{125};
    const auto width{(2 * pieceRadius * numCols) + (2 * numCols * padding)};  // allows for evenly spaced circles across the board
    const auto height{(2 * pieceRadius * numRows) + (2 * numRows * padding)}; // allows for evenly spaced circles top to bottom

    // for keeping track of where the mouse is on the screen (which column)
    auto mouseCol{0};

    bool flip{false};

    board board{};

    // open the window
    sf::RenderWindow window(sf::VideoMode(width, height), "Connect 4!");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        /*
         * event handling
         */
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                mouseCol = event.mouseMove.x * numCols / width;
                break;
            case sf::Event::MouseButtonPressed:
                // place piece on left click
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    flip = !flip;
                    board.insert(flip, mouseCol);
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

        while (colStart < colEnd)
        {
            auto rowStart{(*colStart).begin()};
            auto rowEnd{(*colStart).end()};

            while (rowStart < rowEnd)
            {
                auto colPos{colStart - gameBoard.begin()};
                auto rowPos{rowStart - (*colStart).begin()};

                sf::CircleShape piece(pieceRadius);
                piece.setPosition(padding + (rowPos * 2 * pieceRadius) + (rowPos * padding * 2),
                                  padding + (colPos * 2 * pieceRadius) + (colPos * padding * 2));

                if (*rowStart == 1)
                {
                    piece.setFillColor(sf::Color::Red);
                }
                else if (*rowStart == -1)
                {
                    piece.setFillColor(sf::Color::Yellow);
                }
                else
                {
                    piece.setFillColor(sf::Color::Black);
                }

                window.draw(piece);

                rowStart++;
            }

            colStart++;
        }

        // end the current frame
        window.display();
    }

    return 0;
}