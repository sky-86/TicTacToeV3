#include <iostream>

#include <TGUI/TGUI.hpp>

#include "pages.h"


int main() {
    // initialize the render window and the GUI
    sf::RenderWindow window{{800, 600}, "TicTacToe"};
    tgui::GuiSFML gui{window};
    tgui::Theme::setDefault("BabyBlue.txt");

    pages p(gui);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.waitEvent(event))
        {
            gui.handleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();

            window.clear();
            gui.draw();
            window.display();
        }
    }

    return 0;
}