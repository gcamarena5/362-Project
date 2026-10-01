// Name: Ba Dieu, Justin Lai, Greg Camarena, Liliana Valdez
// Date:9/30/26
#pragma once
#include <iostream>
#include <mysql/jdbc.h>
#include <windows.h>
#include "Input.h"
#include "Item.h"
const int ADJ = 5;

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

// bd:View current inventory ()
// - Needs a bit of work to be pretty but honestly, just for demo for this is all for backend
void inv_view(sql::Statement* stmt, sql::ResultSet* res, bool display = false) {
    int index = 1;
    res = (*stmt).executeQuery("SELECT * FROM inventory;");

    while ((*res).next()) {
        cout << "\n\t[ " + to_string(index) + "] ";
        for (int i = 1; i < ADJ + 1; i++) {
            cout << (*res).getString(i) << " ";
        }
        //cout << (*res).getString(0) << (*res).getString(1) << << endl;
        index++;
    }
    if (display == true) {
    inputChar("\n\tPress enter char then enter");
    }
}

// bd: Add "ITEM" to Database
// - comm: I does not play well with double format but this is due to MYSQL and init_database
void inv_add(sql::Statement* stmt, sql::ResultSet* res) {
    Item test;
    inv_view(stmt, res);

    test.SetSKU(inputString("\n\tSku: ", true));
    test.SetName(inputString("\n\tName: ", true));
    test.SetDescription(inputString("\n\tDescription: ", true));
    test.SetBaseCost(inputDouble("\n\tBase Cost: "));
    test.SetDiscountPercent(0);
    (*stmt).executeUpdate("INSERT INTO inventory " "(sku, name, description, baseCost, discountPercent) VALUES (" + test.GetSummary() + ");");
    inputChar("\n\tPress enter char then enter");
    //cout << "INSERT INTO inventory " "(sku, name, description, baseCost, discountPercent) VALUES (" + test.GetSummary() + ");";
}

// bd: Delete by SKU
// -comm: Modernized so it doesn't use SKU but instead uses loop index
void inv_del(sql::Statement* stmt, sql::ResultSet* res) {
    inv_view(stmt,res);
    (*stmt).executeUpdate("DELETE FROM inventory WHERE sku = \'" + inputString("\n\tWhich sku do you want to delete: ", true) + "';");

    inputChar("\n\tPress enter char then enter");
}

// bd: Edit row in database
// - comm: I does not play well with double format but this is due to MYSQL and init_databse
void inv_edit(sql::Statement* stmt, sql::ResultSet* res) {
    cls();
    inv_view(stmt,res);
    cout << "\n\tVariables: sku, name, description, baseCost, discountPercent\n\n";
    //"UPDATE inventory SET " + string + "WHERE " + string "

    (*stmt).executeUpdate(
        "UPDATE inventory SET " +
        inputString("\n\tWhich variable do you want to change: ", true) +
        " = " +
        inputString("\n\tWhat do you want to change it to: ", true) +
        " WHERE sku = '" +
        inputString("\n\tWhere do you want to change it(SKU): ", true) +
        "';"
    );

    inputChar("\n\tPress enter char then enter");
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