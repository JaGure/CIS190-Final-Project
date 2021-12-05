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
                    board.insert(true, mouseCol);
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

        // draw the board background
        for (auto i{0}; i < numRows; i++)
        {
            for (auto j{0}; j < numCols; j++)
            {
                sf::CircleShape hole(pieceRadius);
                hole.setPosition(padding + (j * 2 * pieceRadius) + (j * padding * 2),
                                 padding + (i * 2 * pieceRadius) + (i * padding * 2));
                hole.setFillColor(sf::Color::Black);
                window.draw(hole);
            }
        }

        // draw the current game state (pieces)
        auto gameBoard{board.getBoard()};

        auto colStart{gameBoard.begin()};
        auto colEnd{gameBoard.end()};

        while (colStart < colEnd)
        {
            auto rowStart{(*colStart).begin()};
            auto rowEnd{(*colStart).end()};

            while (rowStart < rowEnd)
            {
                if (*rowStart == 1 || *rowStart == -1)
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
                    else
                    {
                        piece.setFillColor(sf::Color::Yellow);
                    }

                    window.draw(piece);
                }

                rowStart++;
            }

            colStart++;
        }

        // if (drawNewPiece)
        // {
        //     sf::CircleShape piece(pieceRadius);
        //     piece.setPosition(padding + (mouseCol * 2 * pieceRadius) + (mouseCol * padding * 2), padding);
        //     piece.setFillColor(sf::Color::Red);
        //     window.draw(piece);
        //     drawNewPiece = false;
        // }

        // end the current frame
        window.display();
    }

    return 0;
}