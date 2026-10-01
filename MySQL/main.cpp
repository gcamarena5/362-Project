// Name: Ba Dieu, Justin Lai, Greg Camarena, Liliana Valdez
// Date:9/24/26
 
#include <iostream>
#include<mysql/jdbc.h>
#include <windows.h>
#include "Input.h"
#include "Item.h"
/*
* For SQL builing, future reference, get the debug binaries instead of installation for VS studio coding
* Linker - General - "C:\Users\User\Downloads\Kryptos\mysql-connector-c++-26.7.0-winx64-debug\mysql-connector-c++-26.7.0-winx64\lib64\debug"
* Linker - Input - "C:\Users\User\Downloads\Kryptos\mysql-connector-c++-26.7.0-winx64-debug\mysql-connector-c++-26.7.0-winx64\lib64\debug\vs14\mysqlcppconn.lib"
* C/C++ - General - "C:\Program Files\MySQL\MySQL Connector C++ 26.7\include"
*
* IMPORTANT: Copy and paste the libssl-3-x64.dll, libcrypto-3-x64.dll, mysqlcppconn-10-vs14.dll, mysqlcppconnx-2-vs14.dll and the .pdb too
*/
const int ADJ = 5;

using namespace std;

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

void init_database(sql::Connection *connection) {
    // bd: Statement used for establishing commands like CREATE or DROP.
    sql::Statement* stmt = nullptr;
    
    // bd: Resultset used for returing commands like SELECT.
    sql::ResultSet* res = nullptr;

    // bd: Create Schema test if test does not exist in current database
    stmt = (*connection).createStatement();
    (*stmt).execute("CREATE SCHEMA IF NOT EXISTS test;");
    connection->setSchema("test");

    //bd: Creates table inventory if does not exist and populates with keys.
    (*stmt).execute("CREATE TABLE IF NOT EXISTS inventory(sku VARCHAR(50) PRIMARY KEY, name VARCHAR(100) NOT NULL, description TEXT, baseCost DECIMAL(10, 2) NOT NULL, discountPercent DECIMAL(5, 2) DEFAULT 0.00 );");
    
    delete stmt;
    delete res;
    return;
}

int main() {
    sql::Driver* driver = sql::mysql::get_driver_instance();
    bool pass = false;
    bool running = true;
    
    // bd: Statement used for establishing commands like CREATE or DROP.
    sql::Statement* stmt = nullptr;

    // bd: Resultset used for returing commands like SELECT.
    /*
        while ((*res).next()) {
            cout << (*res).getString("name") << endl;
        }
    */
    sql::ResultSet* res = nullptr;

    
    try {
        sql::Connection* connection = driver->connect("tcp://127.0.0.1:3306", "admin", "toor");
        stmt = (*connection).createStatement();
        cout << "\n\tConnection Sucess!\n";
        Sleep(2000);
        cls();

        init_database(connection);

        Item test;
        int index = 1;
        while (running) {

            switch (menuOption())
            {
            case 1:
                index = 1;
                cls();
                res = (*stmt).executeQuery("SELECT * FROM inventory;");

                while ((*res).next()) {
                    cout << "\n\t[ " + to_string(index) +"] ";
                    for (int i = 1; i < ADJ+1; i++) {
                        cout << (*res).getString(i) << " ";
                    }
                    //cout << (*res).getString(0) << (*res).getString(1) << << endl;
                    index++;
                }

                inputChar("\n\tPress enter char then enter");
                cls();
                index = 1;
                break;
            // bd: Add "ITEM" to Database
            // - ISSUE: I does not play well with double format
            case 2:
                index = 1;
                cls();
                res = (*stmt).executeQuery("SELECT * FROM inventory;");

                while ((*res).next()) {
                    cout << "\n\t[ " + to_string(index) + "] ";
                    for (int i = 1; i < ADJ + 1; i++) {
                        cout << (*res).getString(i) << " ";
                    }
                    //cout << (*res).getString(0) << (*res).getString(1) << << endl;
                    index++;
                }

                test.SetSKU(inputString("\n\tSku: ", true));
                test.SetName(inputString("\n\tName: ", true));
                test.SetDescription(inputString("\n\tDescription: ", true));
                test.SetBaseCost(inputDouble("\n\tBase Cost: "));
                test.SetDiscountPercent(0);
                (*stmt).executeUpdate("INSERT INTO inventory " "(sku, name, description, baseCost, discountPercent) VALUES (" + test.GetSummary() + ");");
                inputChar("\n\tPress enter char then enter");
                //cout << "INSERT INTO inventory " "(sku, name, description, baseCost, discountPercent) VALUES (" + test.GetSummary() + ");";
                cls();
                
                break;
            //Delete by SKU
            case 3:
                cls();
                index = 1;
                cls();
                res = (*stmt).executeQuery("SELECT * FROM inventory;");

                while ((*res).next()) {
                    cout << "\n\t[ " + to_string(index) + "] ";
                    for (int i = 1; i < ADJ + 1; i++) {
                        cout << (*res).getString(i) << " ";
                    }
                    index++;
                }
               
                (*stmt).executeUpdate("DELETE FROM inventory WHERE sku = \'"+ inputString("\n\tWhich sku do you want to delete: ", true) + "';");

                inputChar("\n\tPress enter char then enter");
                index = 1;
                cls();
                break;
            // Edit
            // - ISSUE: It does not play well with double format (assuming)
            case 4:
                index = 1;
                cls();
                res = (*stmt).executeQuery("SELECT * FROM inventory;");

                while ((*res).next()) {
                    cout << "\n\t[ " + to_string(index) + "] ";
                    for (int i = 1; i < ADJ + 1; i++) {
                        cout << (*res).getString(i) << " ";
                    }
                    //cout << (*res).getString(0) << (*res).getString(1) << << endl;
                    index++;
                }
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
                break;
            case 0:
                cls();
                running = false;
                break;
            default:
                break;
            }


        }

            delete connection;
    }
    catch (const sql::SQLException& error) {
            cerr << "SQL error: " << error.what() << '\n';
        
    }
    catch (const std::exception& error) {
        cerr << "Other error: " << error.what() << '\n';
    }
    return 0;
}