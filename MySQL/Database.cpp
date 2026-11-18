#include <exception>
#include <iostream>
#include <set>
#include <windows.h>
#include "Input.h"
#include "Item.h"
#include "Database.h"


//purpose of this is to localize interaction with the database here, and to then connect it to "Menu.h"
// bd:View current inventory ()
// - Needs a bit of work to be pretty but honestly, just for demo for this is all for backend

void inv_view(InventoryRepository& repository, bool display) {
    if (display) {
        cls();
    }
    int index = 1;
    // Ethan: DIP. The query and Big Greg's metadata loop moved to MySqlInventoryRepository::getAll()
    for (const vector<string>& row : repository.getAll()) {
        cout << "\n\t[ " + to_string(index) + "] ";
        for (const string& column : row) {
            cout << column << " ";
        }
        //cout << (*res).getString(0) << (*res).getString(1) << << endl;
        index++;
    }
    if (display) {
        inputChar("\n\tPress enter to continue...");
    }
}


// bd: Add "ITEM" to Database
// - comm: I does not play well with double format but this is due to MYSQL and init_database
void inv_add(InventoryRepository& repository) {
    Item test;
   

    test.SetSKU(inputString("\n\tSku: ", true));
    test.SetName(inputString("\n\tName: ", true));
    test.SetDescription(inputString("\n\tDescription: ", true));
    test.SetBaseCost(inputDouble("\n\tBase Cost: "));
    test.SetDiscountPercent(0);
    repository.add(test); // Ethan: DIP. The INSERT moved to MySqlInventoryRepository::add()
    inputChar("\n\tPress enter to continue...");
    //cout << "INSERT INTO inventory " "(sku, name, description, baseCost, discountPercent) VALUES (" + test.GetSummary() + ");";
}

// bd: Delete by SKU
// -comm: Modernized so it doesn't use SKU but instead uses loop index
void inv_del(InventoryRepository& repository) {

    //Greg - redoing this to use prepared statements. Copying much from the inventory edit

    string skuDelete = inputString("\n\tWhich sku would you like to delete?\n\t", true);
   
    try {

        // Ethan: DIP. The prepared statement moved to MySqlInventoryRepository::remove()
        if (repository.remove(skuDelete)) {
            cout << "\n\tSuccessfully deleted SKU: " << skuDelete << "\n";
        }
        else {
            cout << "\n\tWarning: No item found with SKU: " << skuDelete << "\n";
        }
    }

    catch (std::exception& e) { // Ethan: was sql::SQLException; the repository now rethrows a standard error
        cout << "\n\tDatabase Error: " << e.what() << "\n";
    }
   
    inputChar("\n\tPress enter to continue...");
}


// bd: Edit row in database
// - comm: I does not play well with double format but this is due to MYSQL and init_databse
void inv_edit(InventoryRepository& repository) {
 

    //Greg: edited this to use prepared statements 
    string skuEdit = inputString("\n\tWhich sku would you like to edit?\n\t", true);
  
    cout << "List of columns: name, description, baseCost, discountPercent\n\t";
    string columnEdit = inputString("\n\tWhich column would you like to edit?\n\t", true);

    //establishing a set of columns allowed
    const set<string> allowedColumns =
    {
        "name", "description", "baseCost", "discountPercent"
    };

    //checking if the column is not found
    if (allowedColumns.find(columnEdit) == allowedColumns.end()) {
        cout << "\n\tError: Invalid column name\n";
        inputChar("\n\tPress enter to continue...");
        return;

    }
    string newValue = inputString("\n\tEnter new value for this column\n\t", true);
    try {

        // Ethan: DIP. The prepared statement moved to MySqlInventoryRepository::updateField()
        if (repository.updateField(skuEdit, columnEdit, newValue)) {
            cout << "\n\tSuccessfully updated SKU: " << skuEdit << "\n";
        }
        else {
            cout << "\n\tWarning: No item found with SKU: " << skuEdit << "\n";
        }
    } 

    catch (std::exception& e) { // Ethan: was sql::SQLException; the repository now rethrows a standard error
        cout << "\n\tDatabase Error: " << e.what() << "\n";
    }

    inputChar("\n\tPress enter to continue...");
}