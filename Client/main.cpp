//
// Created by Skyler Favors on 4/6/22.
//

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "gui/gui.h"

int main() {
    gui gui;

    // run the program as long as the window is open
    while (gui.window->isOpen()) {
        // event is a union, only one member is valid at a time
        sf::Event event{};

        while (gui.window->pollEvent(event)) {
            switch (event.type) {

                case sf::Event::Closed:
                    gui.window->close();
                    break;

                case sf::Event::Resized:
                    gui.Update();
                    break;

                default:
                    if (gui.currWindow == "main") {
                        gui.MenuLoop(event);
                    } else if (gui.currWindow == "game") {
                        gui.GameLoop(event);
                    }
                    break;
            }
            gui.Update();
        }
    }
    return 0;
}