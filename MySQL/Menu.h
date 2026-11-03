// Name: Ba Dieu, Justin Lai, Greg Camarena, Liliana Valdez
// Date:9/30/26
#pragma once
#include <iostream>
#include <mysql/jdbc.h>
#include <windows.h>
#include "Input.h"
#include "Item.h"
#include "Data.h"


// bd:Display/cout statement for menu
// - Just a template from my previous 
int menuOption() {
    cout << "\n\tCPSC 362 - MySQL Terminal (demo)"
        << "\n\t" << string(60, char(205))
        << "\n\t 1. View current/Inventory"
        << "\n\t 2. Add Item"
        << "\n\t 3. Remove Item"
        << "\n\t 4. Edit Item"
        << "\n\t" << string(60, char(196))
        << "\n\t 0. Exit"
        << "\n\t" << string(60, char(205)) << endl;
    return inputInteger("\tOption: ", 0, 4);
}


// bd: main menu
// - self explanitory
void _menu_main(sql::Statement* stmt, sql::ResultSet* res) {
    bool running = true;


    while (running) {

        switch (menuOption())
        {
        case 1:
            cls();
            inv_view(stmt,res,true);
            cls();
            break;

        case 2:
            cls();
            inv_add(stmt,res);
            cls();

            break;

        case 3:
            cls();
            inv_del(stmt,res);
            cls();
            break;

        case 4:
            cls();
            inv_edit(stmt, res);
            cls();
            break;
        case 0:
            cls();
            running = false;
            break;
        default:
            break;
        }


    }
}