//
// Created by Skyler Favors on 4/6/22.
//

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "button.h"

button::button(sf::String string, sf::Font& font, float xpos, float ypos, unsigned int charSize, float borderThickness) {
    // create text
    text = sf::Text(string, font, charSize);
    // text options
    sf::Rect<float> textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.width/2, textBounds.height/2);
    text.setPosition(xpos, ypos-10);

    // create box
    textBounds.width += 20;
    textBounds.height += 40;
    box = sf::RectangleShape(sf::Vector2f(textBounds.width, textBounds.height));
    // box options
    box.setOrigin(textBounds.width/2, textBounds.height/2);
    box.setPosition(xpos, ypos);
    box.setFillColor(sf::Color::Transparent);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(borderThickness);
}


void button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
    target.draw(box, states);
}