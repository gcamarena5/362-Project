#pragma once
#include <iostream>
#include <mysql/jdbc.h>
#include "Menu.h"

void _pop_database(sql::Connection* connection) {
    // bd: Statement used for establishing commands like CREATE or DROP.
    sql::Statement* stmt = nullptr;

    // bd: Resultset used for returing commands like SELECT.
    sql::ResultSet* res = nullptr;

    // bd: Create Schema test if test does not exist in current database
    stmt = (*connection).createStatement();
    (*stmt).execute("CREATE SCHEMA IF NOT EXISTS test;");
    connection->setSchema("test");

    //bd: Creates table inventory if does not exist and populates with keys.
    (*stmt).execute("CREATE TABLE IF NOT EXISTS inventory(sku VARCHAR(50) PRIMARY KEY, name VARCHAR(100) NOT NULL, description TEXT, baseCost DECIMAL(10, 2) NOT NULL, discountPercent DECIMAL(10, 6) DEFAULT 0.00 );");

    delete stmt;
    delete res;
    return;
}

void run() {
    sql::Driver* driver = sql::mysql::get_driver_instance();

    // bd: Statement used for establishing commands like CREATE or DROP.
    sql::Statement* stmt = nullptr;

    // bd: Resultset used for returing commands like SELECT.
    /*
    *  - Returning Query
        while ((*res).next()) {
            cout << (*res).getString("name") << endl;
        }
    */
    sql::ResultSet* res = nullptr;


    try {
        //
        sql::Connection* connection = driver->connect("tcp://127.0.0.1:3306", "admin", "toor");
        stmt = (*connection).createStatement();
        cout << "\n\tConnection Sucess!\n";
        Sleep(2000);
        cls();

        _pop_database(connection);
        _menu_main(stmt, res);

        delete connection;
    }
    catch (const sql::SQLException& error) {
        cerr << "SQL error: " << error.what() << '\n';

    }
    catch (const std::exception& error) {
        cerr << "Other error: " << error.what() << '\n';
    }

    return;
}