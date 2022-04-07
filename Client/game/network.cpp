//
// Created by Skyler Favors on 4/6/22.
//

#include <SFML/Network.hpp>
#include <iostream>

#include "network.h"

int network::connect(const std::string& ipPort) {
    std::string tempIp = ipPort.substr(0, ipPort.find(':'));
    std::string tempPort = ipPort.substr(ipPort.find(':')+1, ipPort.length());
    ip = sf::IpAddress(tempIp);
    port = stoi(tempPort);

    // Connect to server
    sf::Socket::Status status = socket.connect(ip, port);
    if (status != sf::Socket::Done){
        std::cout << "Error: can't connect to server" << std::endl;
        return -1;
    }
    std::cout << "Client: Connected" << std::endl;

    // wait for connection confirmation
    sf::Packet confirmPacket;
    if (socket.receive(confirmPacket) != sf::Socket::Done) {
        std::cout << "Error: confirmation packet" << std::endl;
        return -1;
    }
    std::string confirmationMsg;
    confirmPacket >> confirmationMsg;
    std::cout << confirmationMsg << std::endl;

    // wait for player assignments
    std::cout << "Waiting for player assignments" << std::endl;
    sf::Packet assignmentPacket;
    sf::Uint16 playerNum;
    if (socket.receive(assignmentPacket) != sf::Socket::Done) {
        std::cout << "Error: assignment packet" << std::endl;
        return -1;
    }
    assignmentPacket >> playerNum;
    std::cout << "Assigned " << playerNum << std::endl;


    std::cout << "Starting game" << std::endl;

    connected = true;
    return playerNum;
}

void network::endTurn(sf::Int8 isOver, sf::Int8 x, sf::Int8 y) {
    sf::Packet outPacket;
    outPacket << isOver << x << y;

    if (socket.send(outPacket) != sf::Socket::Done) {
        std::cout << "Error: sending end turn packet" << std::endl;
    }
}

sf::Packet network::waitTurn() {
    sf::Packet inPacket;
    if (socket.receive(inPacket) != sf::Socket::Done) {
        std::cout << "Error: receiving wait turn packet" << std::endl;
    }

    return inPacket;
}