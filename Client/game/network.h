//
// Created by Skyler Favors on 4/6/22.
//

#ifndef TICTACTOECLIENT_NETWORK_H
#define TICTACTOECLIENT_NETWORK_H


class network {
private:

    struct coordPacket {
        sf::Int8 xpos;
        sf::Int8 ypos;
    };

public:
    sf::TcpSocket socket;
    sf::IpAddress ip;
    unsigned int port;
    bool connected = false;

    int connect(const std::string& ipPort);
    void endTurn(sf::Int8 isOver, sf::Int8 x, sf::Int8 y);
    sf::Packet waitTurn();
};


#endif //TICTACTOECLIENT_NETWORK_H
