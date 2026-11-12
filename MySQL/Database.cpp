#include <iostream>
#include <mysql/jdbc.h>
#include <set>
#include <memory>
#include <windows.h>
#include "Input.h"
#include "Item.h"
#include "Database.h"

using namespace std;

// Checks whether an inventory SKU already exists.
// Uses a prepared statement so the SKU is treated as data, not SQL.
static bool skuExists(sql::Statement* stmt, const string& sku) {
    try {
        sql::Connection* connection = stmt->getConnection();
        unique_ptr<sql::PreparedStatement> pstmt(
            connection->prepareStatement("SELECT 1 FROM inventory WHERE sku = ? LIMIT 1"));
        pstmt->setString(1, sku);

        unique_ptr<sql::ResultSet> result(pstmt->executeQuery());
        return result->next();
    }
    catch (const sql::SQLException& e) {
        cout << "\n\tDatabase Error while checking SKU: " << e.what() << "\n";
        return false;
    }
}


// View current inventory.
void inv_view(sql::Statement* stmt, sql::ResultSet* res, bool display) {
    if (display) cls();

    int index = 1;
    res = stmt->executeQuery("SELECT * FROM inventory;");
    sql::ResultSetMetaData* metaData = res->getMetaData();
    int numColumns = metaData->getColumnCount();

    while (res->next()) {
        cout << "\n\t[ " << index << "] ";
        for (int i = 1; i <= numColumns; i++) {
            cout << res->getString(i) << " ";
        }
        index++;
    }

    if (display) inputChar("\n\tPress enter to continue...");
}

// Add an item. Reject a SKU that is already present.
void inv_add(sql::Statement* stmt, sql::ResultSet* res) {
    Item item;

    string sku = inputString("\n\tSKU: ", true, false);
    if (skuExists(stmt, sku)) {
        cout << "\n\tError: An item with SKU '" << sku << "' already exists.\n";
        inputChar("\n\tPress enter to continue...");
        return;
    }

    item.SetSKU(sku);
    item.SetName(inputString("\n\tName: ", true, false));
    item.SetDescription(inputString("\n\tDescription: ", true, true));
    item.SetBaseCost(inputDouble("\n\tBase Cost: ", 0.0, true));
    item.SetDiscountPercent(0);

    // NOTE: This INSERT is still a Statement. Convert it to a PreparedStatement
    // separately (the prepared-statement task) to avoid SQL injection.
    try {
        stmt->executeUpdate(
            "INSERT INTO inventory (sku, name, description, baseCost, discountPercent) VALUES ("
            + item.GetSummary() + ");");
        cout << "\n\tItem added successfully.\n";
    }
    catch (const sql::SQLException& e) {
        cout << "\n\tDatabase Error: " << e.what() << "\n";
    }

    inputChar("\n\tPress enter to continue...");
}

// Delete by SKU. Verify that the item exists before running DELETE.
void inv_del(sql::Statement* stmt, sql::ResultSet* res) {
    string skuDelete = inputString("\n\tWhich SKU would you like to delete?\n\t", true, false);

    if (!skuExists(stmt, skuDelete)) {
        cout << "\n\tNo item exists with SKU '" << skuDelete << "'. Nothing was deleted.\n";
        inputChar("\n\tPress enter to continue...");
        return;
    }

    try {
        sql::Connection* connection = stmt->getConnection();
        unique_ptr<sql::PreparedStatement> pstmt(
            connection->prepareStatement("DELETE FROM inventory WHERE sku = ?"));
        pstmt->setString(1, skuDelete);

        int rowsAffected = pstmt->executeUpdate();
        if (rowsAffected > 0)
            cout << "\n\tSuccessfully deleted SKU: " << skuDelete << "\n";
        else
            cout << "\n\tItem was not deleted; it may have been removed by another user.\n";
    }
    catch (const sql::SQLException& e) {
        cout << "\n\tDatabase Error: " << e.what() << "\n";
    }

    inputChar("\n\tPress enter to continue...");
}

// Edit an item. Verify SKU existence before asking for the column/value.
void inv_edit(sql::Statement* stmt, sql::ResultSet* res) {
    string skuEdit = inputString("\n\tWhich SKU would you like to edit?\n\t", true, false);

    if (!skuExists(stmt, skuEdit)) {
        cout << "\n\tNo item exists with SKU '" << skuEdit << "'. Nothing was changed.\n";
        inputChar("\n\tPress enter to continue...");
        return;
    }

    cout << "List of columns: name, description, baseCost, discountPercent\n\t";
    string columnEdit = inputString("\n\tWhich column would you like to edit?\n\t", true, false);

    // Only these fixed column names may be inserted into the UPDATE query.
    const set<string> allowedColumns = {
        "name", "description", "baseCost", "discountPercent"
    };

    if (allowedColumns.find(columnEdit) == allowedColumns.end()) {
        cout << "\n\tError: Invalid column name.\n";
        inputChar("\n\tPress enter to continue...");
        return;
    }

    string newValue;
    if (columnEdit == "name") {
        newValue = inputString("\n\tEnter new name: ", true, false);
    }
    else if (columnEdit == "description") {
        newValue = inputString("\n\tEnter new description: ", true, true);
    }
    else if (columnEdit == "baseCost") {
        newValue = to_string(inputDouble("\n\tEnter new base cost: ", 0.0, true));
    }
    else { // discountPercent
        // Database column stores a decimal fraction: 0.15 means 15%.
        newValue = to_string(inputDouble("\n\tEnter discount (0.00 to 1.00): ", 0.0, 1.0));
    }

    try {
        sql::Connection* connection = stmt->getConnection();
        string query = "UPDATE inventory SET " + columnEdit + " = ? WHERE sku = ?";
        unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));
        pstmt->setString(1, newValue);
        pstmt->setString(2, skuEdit);

        int rowsAffected = pstmt->executeUpdate();
        if (rowsAffected > 0)
            cout << "\n\tSuccessfully updated SKU: " << skuEdit << "\n";
        else
            cout << "\n\tNo values changed. The item may have been modified by another user.\n";
    }
    catch (const sql::SQLException& e) {
        cout << "\n\tDatabase Error: " << e.what() << "\n";
    }

    inputChar("\n\tPress enter to continue...");
}
