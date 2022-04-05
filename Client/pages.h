//
// Created by Skyler Favors on 4/4/22.
//

#ifndef TICTACTOECLIENT_PAGES_H
#define TICTACTOECLIENT_PAGES_H

#include <TGUI/TGUI.hpp>

class pages {
private:
    std::vector<std::shared_ptr<tgui::Group>> groups;

    std::shared_ptr<tgui::Group> mainMenu = tgui::Group::create();
    std::shared_ptr<tgui::Group> spMenu = tgui::Group::create();
    std::shared_ptr<tgui::Group> mpMenu = tgui::Group::create();
    std::shared_ptr<tgui::Group> optionsMenu = tgui::Group::create();

    void showMainMenu();
    void showSPmenu();
    void showMPmenu();
    void showOptions();
    void updateTextSize(tgui::GuiBase& gui);
    void loadWidgets(tgui::GuiBase& gui);

    void loadMainMenu();

public:
    explicit pages(tgui::GuiBase& gui) {
        groups.push_back(mainMenu);
        groups.push_back(spMenu);
        groups.push_back(mpMenu);
        groups.push_back(optionsMenu);

        loadWidgets(gui);
    }
};


#endif //TICTACTOECLIENT_PAGES_H
