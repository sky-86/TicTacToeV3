#include <iostream>
#include <SFML/Network.hpp>
#include <random>
#include <algorithm>

int establishConnection();
int assignPlayers();

int gameLoop();

std::vector<sf::TcpSocket*> sockets;

int main() {
    establishConnection();

    assignPlayers();

    gameLoop();

    return 0;
}

int establishConnection() {
    unsigned short port = 53000;
    sf::TcpListener listener;

    // Wait for incoming connection
    if (listener.listen(port) != sf::Socket::Done) {
        std::cout << "Error: establishing listener" << std::endl;
        return -1;
    }
    std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

    // connect to two clients
    int i = 0;
    while (i != 2) {
        auto *socket = new sf::TcpSocket;

        if (listener.accept(*socket) != sf::Socket::Done) {
            std::cout << "Error: accepting connection" << std::endl;
            continue;
        }
        std::cout << "Client connected: " << socket->getRemoteAddress() << std::endl;
        sockets.push_back(socket);

        // Send a message to the connected client
        sf::Packet outPacket;
        outPacket << "Server: Connected";

        if (socket->send(outPacket) != sf::Socket::Done) {
            std::cout << "Error: sending confirmation packet" << std::endl;
            continue;
        }

        std::cout << "Confirmation Message sent" << std::endl;
        i++;
    }

    return 0;
}

int assignPlayers() {
    // shuffle the sockets around
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(sockets), std::end(sockets), rng);

    int i = 0;
    while (i != 2) {
        sf::Packet outPacket;
        sf::Uint16 num = (i + 1);
        outPacket << num;

        if (sockets[i]->send(outPacket) != sf::Socket::Done) {
            std::cout << "Error: Sending playing assignments" << std::endl;
            continue;
        }
        i++;
    }
    std::cout << "Players assigned" <<  std::endl;

    return 1;
}

int gameLoop() {
    sf::Packet inPacket;
    sf::Int8 gameOver;

    // 0 = game in progress
    // 1 = end game
    // 2 = play again

    while(true) {
        for (int i = 0; i < 2; i++) {
            std::cout << "Waiting for turn packet" << std::endl;

            if (sockets[i]->receive(inPacket) != sf::Socket::Done) {
                std::cout << "Error: receiving turn packet" << std::endl;
                break;
            }
            std::cout << "Received Turn Packet" << std::endl;

            if (i == 0) {
                sockets[1]->send(inPacket);
            } else {
                sockets[0]->send(inPacket);
            }

            inPacket >> gameOver;
            if (gameOver == 1) {
                std::cout << "Game is over" << std::endl;

                int count = 0;
                for (int j = 0; j < 2; j++) {
                    // check if players want to play again
                    if (sockets[j]->receive(inPacket) != sf::Socket::Done) {
                        std::cout << "Error: receiving play again packet" << std::endl;
                        return -1;
                    }
                    sf::Int8 playAgain;
                    inPacket >> playAgain;
                    int temp = (int) playAgain;

                    std::cout << "Received packet " << temp << std::endl;

                    if (temp == 2) {
                        count++;
                    }
                }
                if (count == 2) {
                    // players want to play again
                    gameOver = false;
                } else {
                    return -1;
                }
            }
        }
    }
}
