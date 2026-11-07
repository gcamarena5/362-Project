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

void inv_view(sql::Statement* stmt, sql::ResultSet* res, bool display) {
    if (display) {
        cls();
    }
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
    if (display) {
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

        //getting the connection so we can use prepared statements
        sql::Connection* connection = stmt->getConnection();
        string query = "UPDATE inventory SET " + columnEdit + " = ? WHERE sku = ?";

        unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));

        //ind parameters safely
        pstmt->setString(1, newValue);
        pstmt->setString(2, skuEdit);

        int rowsAffected = pstmt->executeUpdate();

        //if true the value will be more than 0, meaning our database was updated
        if (rowsAffected > 0) {
            cout << "\n\tSuccessfully updated SKU: " << skuEdit << "\n";
        }
        else {
            cout << "\n\tWarning: No item found with SKU: " << skuEdit << "\n";
        }
    } 

    catch (sql::SQLException& e) {
        cout << "\n\tDatabase Error: " << e.what() << "\n";
    }

    inputChar("\n\tPress enter to continue...");
}