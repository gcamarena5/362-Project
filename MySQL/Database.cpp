#include <iostream>
#include <mysql/jdbc.h>
#include <set>
#include <windows.h>
#include "Input.h"
#include "Item.h"
#include "Database.h"


//purpose of this is to localize interaction with the database here, and to then connect it to "Menu.h"
// bd:View current inventory ()
// - Needs a bit of work to be pretty but honestly, just for demo for this is all for backend

void inv_view(sql::Statement* stmt, sql::ResultSet* res, bool display = false) {
    int index = 1;
    res = (*stmt).executeQuery("SELECT * FROM inventory;");
    //Greg - Getting the metadata to then get the column data to remove any hard-coded constants
    sql::ResultSetMetaData* metaData = res->getMetaData();

    int numColumns = metaData->getColumnCount();

    while ((*res).next()) {
        cout << "\n\t[ " + to_string(index) + "] ";
        for (int i = 1; i < numColumns + 1; i++) {
            cout << (*res).getString(i) << " ";
        }
        //cout << (*res).getString(0) << (*res).getString(1) << << endl;
        index++;
    }
    if (display == true) {
        inputChar("\n\tPress enter to continue...");
    }
}


// bd: Add "ITEM" to Database
// - comm: I does not play well with double format but this is due to MYSQL and init_database
void inv_add(sql::Statement* stmt, sql::ResultSet* res) {
    Item test;
   

    test.SetSKU(inputString("\n\tSku: ", true));
    test.SetName(inputString("\n\tName: ", true));
    test.SetDescription(inputString("\n\tDescription: ", true));
    test.SetBaseCost(inputDouble("\n\tBase Cost: "));
    test.SetDiscountPercent(0);
    (*stmt).executeUpdate("INSERT INTO inventory " "(sku, name, description, baseCost, discountPercent) VALUES (" + test.GetSummary() + ");");
    inputChar("\n\tPress enter to continue...");
    //cout << "INSERT INTO inventory " "(sku, name, description, baseCost, discountPercent) VALUES (" + test.GetSummary() + ");";
}

// bd: Delete by SKU
// -comm: Modernized so it doesn't use SKU but instead uses loop index
void inv_del(sql::Statement* stmt, sql::ResultSet* res) {
    
    (*stmt).executeUpdate("DELETE FROM inventory WHERE sku = \'" + inputString("\n\tPlease enter the sku to be deleted: ", true) + "';");

    inputChar("\n\tPress enter to continue...");
}


// bd: Edit row in database
// - comm: I does not play well with double format but this is due to MYSQL and init_databse
void inv_edit(sql::Statement* stmt, sql::ResultSet* res) {
    cls();

    cout << "\n\tVariables: sku, name, description, baseCost, discountPercent\n\n";
    //"UPDATE inventory SET " + string + "WHERE " + string "

/*

string column = inputString("\n\tWhich variable would you like to edit?", true);

    const set<string> allowedColumns = {
        "sku", "name", "description", "baseCost", "discountPercent"
    };

    if (allowedColumns.find(column) == allowedColumns.end()) {
        cout << "\n\tError. Invalid column name\n";
        inputChar("\n\tPress enter to continue...");
        return;
    }
*/
    string inputSku = inputString("\n\tWhich Sku would you like to edit?", true);


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
