// Name: Ba Dieu, Justin Lai, Greg Camarena, Liliana Valdez, Ethan Villa
// Date:11/10/26
#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include "Input.h"
#include "Item.h"
#include "MenuCommand.h"


// bd:Display/cout statement for menu
// - Just a template from my previous
// Ethan: OCP. The option lines come from each command's label() instead of being typed here.
int menuOption(const vector<MenuCommand*>& commands) {
    cout << "\n\tGroup 5 Auto Warehouse"
        << "\n\t" << string(60, char(205));
    for (size_t i = 0; i < commands.size(); i++) {
        cout << "\n\t " << (i + 1) << ". " << commands[i]->label();
    }
    cout << "\n\t" << string(60, char(196))
        << "\n\t 0. Exit"
        << "\n\t" << string(60, char(205)) << endl;
    return inputInteger("\tOption: ", 0, static_cast<int>(commands.size()));
}


// bd: main menu
// - self explanitory
// Ethan: DIP, It no longer takes MySQL's stmt and res.
void _menu_main(const vector<MenuCommand*>& commands) {
    bool running = true;


    while (running) {

        int choice = menuOption(commands);
        cls();

        if (choice == 0) {
            running = false;
        }
        else {
            commands[choice - 1]->run();
            cls();
        }


    }
}