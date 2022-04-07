//
// Created by Skyler Favors on 4/6/22.
//

#ifndef TICTACTOECLIENT_GUI_H
#define TICTACTOECLIENT_GUI_H

#include "button.h"
#include "../game/network.h"
#include "../game/game.h"

class gui {
private:
    struct MainMenuObjects {
        std::unique_ptr<sf::Text> title;
        std::unique_ptr<sf::Text> textbox;
        std::unique_ptr<sf::Text> input;
        std::unique_ptr<button> btnStart;
    };

    struct GameObjects {
        std::vector<std::unique_ptr<sf::RectangleShape>> grid;
    };

    sf::Vector2<float> mousePosition = sf::Vector2<float>(0, 0);
    MainMenuObjects menuObjects;
    GameObjects gameObjects;
    network n;
    game g;


    void DrawMain();
    void DrawGame();
    void LoadMain();
    void LoadGame();

public:
    std::unique_ptr<sf::RenderWindow> window;
    sf::Font font;
    sf::String currWindow = "main";
    sf::String input = "";


    gui();
    void Update();
    void MenuLoop(sf::Event& event);
    void GameLoop(sf::Event& event);
};


#endif //TICTACTOECLIENT_GUI_H
