//
// Created by Skyler Favors on 4/4/22.
//

#include "pages.h"


void pages::showMainMenu() {
    for (const auto& group : groups) {
        group->setVisible(false);
    }
    mainMenu->setVisible(true);
}

void pages::showSPmenu() {
    for (const auto& group : groups) {
        group->setVisible(false);
    }
    spMenu->setVisible(true);
}

void pages::showMPmenu() {

}

void pages::showOptions() {

}

void pages::updateTextSize(tgui::GuiBase& gui)
{
    // Update the text size of all widgets in the gui, based on the current window height
    const float windowHeight = gui.getView().getRect().height;
    gui.setTextSize(static_cast<unsigned int>(0.07f * windowHeight)); // 7% of height
}

void pages::loadWidgets(tgui::GuiBase& gui) {

    // Specify an initial text size instead of using the default value
    updateTextSize(gui);
    // We want the text size to be updated when the window is resized
    gui.onViewChange([&gui, this]{ updateTextSize(gui); });

    // ---- Main menu
    tgui::Button::Ptr button = tgui::Button::create("Hello");
    button->setSize("20%","10%");
    button->setOrigin(0.5f, 0.5f);
    button->setPosition("50%", "10%");
    button->onPress(&pages::showSPmenu, this);
    mainMenu->add(button);

    // ---- SinglePlayer menu
    tgui::Label::Ptr label = tgui::Label::create("Hello test page");
    label->setSize("50%","10%");
    label->setOrigin(0.5f, 0.5f);
    label->setPosition("50%", "10%");
    spMenu->add(label);

    tgui::Button::Ptr newButton = tgui::Button::copy(button);
    newButton->onPress(&pages::showMainMenu, this);
    newButton->setPosition("50%", "50%");
    newButton->setText("Back");
    spMenu->add(newButton);


    // ---- Multiplayer Menu



    // ---- Options Menu

    gui.add(mainMenu);
    gui.add(spMenu);
    showMainMenu();
}

void pages::loadMainMenu() {
    tgui::Button::Ptr button = tgui::Button::create("Hello");
    button->setSize("20%","10%");
    button->setOrigin(0.5f, 0.5f);
    button->setPosition("50%", "10%");
    button->onPress(&pages::showSPmenu, this);
    mainMenu->add(button);
}