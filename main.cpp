#include <SFML/Graphics.hpp>

#include "game.hpp"
#include <iostream>

int main() {
    sf::Font font;
    if (!font.loadFromFile("coolvetica rg.otf")) {
        std::cerr << "Could not load font"
                  << "\n";
        exit(1);
    }

    game game;

    // open the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Connect 4!");

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
                game.setSelectedCol(event.mouseMove.x * NUM_COLS / WIDTH);
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left && !game.isDone()) game.addPiece();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::R) {
                    game.reset();
                }
            default:
                break;
            }
        }

        game.drawTo(window, font);

        // end the current frame
        window.display();
    }

    return 0;
}