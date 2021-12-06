#include <SFML/Network.hpp>
#include <iostream>
#include <signal.h>

sf::TcpSocket player1;
sf::TcpSocket player2;

// graceful cleanup.
void sigint_handler(int signal)
{
    player1.disconnect();
    player2.disconnect();
    exit(0);
}

int main()
{
    signal(SIGINT, sigint_handler);
    sf::TcpListener listener;
    int data[2];
    std::size_t received;

    // bind the listener to a port
    if (listener.listen(53000) != sf::Socket::Done)
    {
        std::cout << "listener error\n";
    }

    std::cout << "bound listener to port 53000\n";

    // accept a new connection

    if (listener.accept(player1) != sf::Socket::Done)
    {
        std::cout << "client acception error\n";
    }

    std::cout << "player1 connected\n";

    if (listener.accept(player2) != sf::Socket::Done)
    {
        std::cout << "client acception error\n";
    }

    listener.close();

    std::cout << "player2 connected\n";

    // marshal data between the two clients
    while (1)
    {

        if (player1.receive(data, sizeof(int) * 2, received) != sf::Socket::Done)
        {
            std::cout << "error recieving data from player1\n";
        }
        else
        {
            std::cout << "got column " << data[1] << " from player1\n";
        }

        if (player2.send(data, sizeof(int) * 2) != sf::Socket::Done)
        {
            std::cout << "error sending data to player2\n";
        };

        if (player2.receive(data, sizeof(int) * 2, received) != sf::Socket::Done)
        {
            std::cout << "error recieving data from player2\n";
        }
        else
        {
            std::cout << "got column " << data[1] << " from player2\n";
        }

        if (player1.send(data, sizeof(int) * 2) != sf::Socket::Done)
        {
            std::cout << "error sending data to player1\n";
        };
    }
}
