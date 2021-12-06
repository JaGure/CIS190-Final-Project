#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::TcpListener listener;
    int *data = new int;
    std::size_t received;

    // bind the listener to a port
    if (listener.listen(53000) != sf::Socket::Done) {
        std::cout << "listener error\n";
    }

    std::cout << "bound listener to port 53000\n";

    // accept a new connection
    sf::TcpSocket player1;
    sf::TcpSocket player2;
    if (listener.accept(player1) != sf::Socket::Done) {
        std::cout << "client acception error\n";
    }

    std::cout << "player1 connected\n";

    if (listener.accept(player2) != sf::Socket::Done) {
        std::cout << "client acception error\n";
    }

    std::cout << "player2 connected\n";

    while (1) {

        if (player1.receive(data, sizeof(int), received) != sf::Socket::Done) {
            std::cout << "error recieving data from player1\n";
        } else {
            std::cout << "got column " << *data << " from player1\n";
        }

        if (player2.send(data, sizeof(int)) != sf::Socket::Done) {
            std::cout << "error sending data to player2\n";
        };

        if (player2.receive(data, sizeof(int), received) != sf::Socket::Done) {
            std::cout << "error recieving data from player2\n";
        } else {
            std::cout << "got column " << *data << " from player2\n";
        }

        if (player1.send(data, sizeof(int)) != sf::Socket::Done) {
            std::cout << "error sending data to player1\n";
        };
    }
}
