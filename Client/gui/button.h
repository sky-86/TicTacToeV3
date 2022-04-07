//
// Created by Skyler Favors on 4/6/22.
//

#ifndef TICTACTOECLIENT_BUTTON_H
#define TICTACTOECLIENT_BUTTON_H


class button : public sf::Drawable {
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    sf::Text text;
    sf::RectangleShape box;

    button(sf::String string, sf::Font& font, float xpos, float ypos, unsigned int charSize, float borderThickness);
};


#endif //TICTACTOECLIENT_BUTTON_H
