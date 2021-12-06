#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "game.hpp"
#include <iostream>

int main(int argc, char **argv)
{

    // for loading the game client
    const char *IP_ADDR = argc > 1 ? argv[1] : "127.0.0.1";
    std::cout << "expects host at: " << IP_ADDR << std::endl;

    sf::TcpSocket socket;
    std::size_t received;
    int data[2];
    bool socketOpen = false;

    // load in the font
    sf::Font font;
    if (!font.loadFromFile("coolvetica rg.otf"))
    {
        std::cerr << "Could not load font"
                  << "\n";
        exit(1);
    }

    // initialize the game
    game game{};
    int botTimer = 0;

    // open the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Connect 4!");

    // run the program as long as the window is open
    while (window.isOpen())
    {

        // Handle recieves on this socket.
        if (game.hasStarted() && socketOpen && socket.receive(data, sizeof(int) * 2, received) == sf::Socket::Done)
        {
            switch (data[0])
            {
            case 0: // 0 denotes inserting a piece command
                game.setSelectedCol(data[1]);
                game.addPiece();
                break;
            case 1: // 1 denotes reseting the game.
                game.reset();
                break;
            }
        }

        /*
         * event handling (within this window)
         */
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                if (socketOpen)
                    socket.disconnect();
                break;
            case sf::Event::MouseMoved:
                if (game.hasStarted())
                    game.setSelectedCol(event.mouseMove.x * NUM_COLS / WIDTH);
                break;
            case sf::Event::MouseButtonPressed:
                if (botTimer == 0 && event.mouseButton.button == sf::Mouse::Left && !game.isDone() && game.hasStarted())
                {
                    game.addPiece();
                    if (game.vsBot())
                    {
                        // for adding the bot's piece (below)
                        botTimer = 500;
                    }
                    else
                    {
                        data[0] = 0;
                        data[1] = game.getSelectedCol();
                        if (socket.send(data, sizeof(int) * 2) != sf::Socket::Done)
                        {
                            std::cout << "error sending data\n";
                        };
                    }
                }

                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::R:
                    game.reset();
                    if (!game.vsBot())
                    {
                        data[0] = 1;
                        if (socket.send(data, sizeof(int) * 2) != sf::Socket::Done)
                        {
                            std::cout << "error sending data\n";
                        };
                    }
                    break;
                case sf::Keyboard::Num1:
                    if (!game.hasStarted())
                        game.start(false);
                    break;
                case sf::Keyboard::Num2:
                    if (!game.hasStarted())
                    {
                        game.start(true);
                        if (!socketOpen)
                        {
                            if (socket.connect(IP_ADDR, 53000) != sf::Socket::Done)
                            {
                                std::cout << "socket connection error\n";
                            }
                            socket.setBlocking(false);
                            socketOpen = true;
                        }
                    }

                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        game.drawTo(window, font);
        game.tick();
        if (botTimer > 0)
        {
            botTimer--;
            if (botTimer == 0)
            {
                game.addPiece();
            }
        }

        // end the current frame
        window.display();
    }
    return 0;
}