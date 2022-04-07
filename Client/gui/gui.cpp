//
// Created by Skyler Favors on 4/6/22.
//

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#include "gui.h"
#include "button.h"
#include "../game/game.h"
#include "../game/network.h"

/*
 *
 */
gui::gui() {
    // Initialize the main window
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "TicTacToe");
    window->setVerticalSyncEnabled(true);
    window->clear(sf::Color::Black);
    // Initialize font
    if (!font.loadFromFile("IBMPlexMono-Bold.ttf")) {
        std::cout << "Failed to load font" << std::endl;
    }

    LoadMain();
    LoadGame();
}

/* Updates all objects in window
 *
 */
void gui::Update() {
    window->clear(sf::Color::Black);

    if (currWindow == "main") {
        DrawMain();
    }
    else if (currWindow == "game") {
        DrawGame();
    }

    window->display();
}

void gui::DrawMain() {
    window->draw(*menuObjects.title);
    window->draw(*menuObjects.textbox);

    // update the origin and position of the input box
    // so that it stays in the center
    sf::Rect<float> inputBounds = menuObjects.input->getLocalBounds();
    menuObjects.input->setOrigin(inputBounds.width/2, inputBounds.height/2);
    menuObjects.input->setPosition(400, 320);

    window->draw(*menuObjects.input);
    window->draw(*menuObjects.btnStart);
}

void gui::DrawGame() {
    for (auto& btn : gameObjects.grid) {
        window->draw(*btn);
    }
}

void gui::LoadMain() {
    menuObjects.title = std::make_unique<sf::Text>(sf::Text("TicTacToe", font, 60));
    sf::Rect<float> titleBounds = menuObjects.title->getLocalBounds();
    menuObjects.title->setOrigin(titleBounds.width/2, titleBounds.height/2);
    menuObjects.title->setPosition(400, 75);

    menuObjects.textbox = std::make_unique<sf::Text>(sf::Text("Enter IP:PORT", font, 40));
    sf::Rect<float> textboxBounds = menuObjects.textbox->getLocalBounds();
    menuObjects.textbox->setOrigin(textboxBounds.width/2, textboxBounds.height/2);
    menuObjects.textbox->setPosition(400, 250);

    menuObjects.input = std::make_unique<sf::Text>(sf::Text("", font, 40));
    sf::Rect<float> inputBounds = menuObjects.input->getLocalBounds();
    menuObjects.input->setOrigin(inputBounds.width/2, inputBounds.height/2);
    menuObjects.input->setPosition(400, 320);

    menuObjects.btnStart = std::make_unique<button>(button("Start", font, 400, 500, 50, 1));
}

void gui::LoadGame() {
    auto size = window->getSize();
    auto width = (float) size.x;
    auto height = (float) size.y;

    int i = 0;
    for (int y=0; y<3; y++) {
        for (int x=0; x<3; x++) {
            gameObjects.grid.push_back(std::make_unique<sf::RectangleShape>(sf::Vector2f(width / 3, height / 3)));

            gameObjects.grid[i]->setOutlineThickness(1);
            gameObjects.grid[i]->setOutlineColor(sf::Color::White);
            gameObjects.grid[i]->setFillColor(sf::Color::Black);
            gameObjects.grid[i]->setPosition((float) x * width / 3, (float) y * height / 3);
            i++;
        }
    }
}

void gui::MenuLoop(sf::Event& event) {
    switch (event.type) {

        case sf::Event::TextEntered:
            if(event.text.unicode == 8) {
                input = input.substring(0, input.getSize()-1);
                menuObjects.input->setString(input);
            }
            else if(event.text.unicode > 47 && event.text.unicode <= 58 && input.getSize() < 21 || event.text.unicode == 46) {
                input += event.text.unicode;
                menuObjects.input->setString(input);
            }
            else if (event.text.unicode == 10) {
                // pressed enter, do the same as clicking start

                if (input.find(':') == sf::String::InvalidPos) {
                    std::cout << "invalid IP:PORT" << std::endl;
                } else {
                    currWindow = "game";
                }
            }

            Update();
            break;

        case sf::Event::MouseButtonReleased:
            mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

            if (menuObjects.btnStart->box.getGlobalBounds().contains(mousePosition)) {
                // Clicked
                if (input.find(':') == sf::String::InvalidPos) {
                    std::cout << "invalid IP:PORT" << std::endl;
                } else {
                    currWindow = "game";
                }
            }

            Update();
            break;

        case sf::Event::MouseMoved:
            mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

            if (menuObjects.btnStart->box.getGlobalBounds().contains(mousePosition)) {
                menuObjects.btnStart->box.setFillColor(sf::Color(0,0,255,128));
            }
                // set button back to its original color
            else if (menuObjects.btnStart->box.getFillColor() != sf::Color::Transparent) {
                menuObjects.btnStart->box.setFillColor(sf::Color::Transparent);
            }

            Update();
            break;

        default:
            break;
    }
}

void gui::GameLoop(sf::Event &event) {
    // checks if its connected, if not it trys to connect
    if (!n.connected) {
        int playerNum = n.connect(menuObjects.input->getString());
        if (playerNum == -1) {
            sf::sleep(sf::milliseconds(500));
        } else {
            if (playerNum == 1) {
                g.yourTurn = true;
            }
        }
    }

    // opponents move
    if (!g.yourTurn && !g.isOver) {
        sf::Packet inPacket = n.waitTurn();
        sf::Int8 isOver;
        sf::Int8 x;
        sf::Int8 y;
        inPacket >> isOver >> x >> y;
        g.PlaceMarker(x, y);
        g.yourTurn = true;

        if (isOver == 1) {
            g.isOver = true;
        }

        gameObjects.grid[y*3+x]->setFillColor(sf::Color::Red);
        Update();
    }

    if (g.isOver) {
        std::cout << "Game is over" << std::endl;
        sf::sleep(sf::seconds(3));
        window->close();
    }

    switch (event.type) {

        case sf::Event::MouseButtonReleased:

            if (g.yourTurn && !g.isOver) {
                // your turn
                mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

                for (int i=0; i<gameObjects.grid.size(); i++) {
                    auto &s = gameObjects.grid[i];

                    if (s->getGlobalBounds().contains(mousePosition)) {
                        int x = i % 3;
                        int y = i / 3;
                        if (g.PlaceMarker(x, y)) {
                            g.yourTurn = false;
                            if (g.WinCheck()) {
                                n.endTurn(1,(sf::Int8) x,(sf::Int8) y);
                            } else {
                                n.endTurn(0,(sf::Int8) x,(sf::Int8) y);
                            }

                            s->setFillColor(sf::Color::Blue);
                        }
                    }
                }
            }
            Update();
            break;

        case sf::Event::MouseMoved:
            break;

        default:
            Update();
            break;
    }
}
