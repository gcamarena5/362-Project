// Name: Ba Dieu
// Date:9/24/26
// 
#include <iostream>
#include<mysql/jdbc.h>
/*
* For SQL builing, future reference, get the debug binaries instead of installation for VS studio coding
* Linker - General - "C:\Users\User\Downloads\Kryptos\mysql-connector-c++-26.7.0-winx64-debug\mysql-connector-c++-26.7.0-winx64\lib64\debug"
* Linker - Input - "C:\Users\User\Downloads\Kryptos\mysql-connector-c++-26.7.0-winx64-debug\mysql-connector-c++-26.7.0-winx64\lib64\debug\vs14\mysqlcppconn.lib"
* C/C++ - General - "C:\Program Files\MySQL\MySQL Connector C++ 26.7\include"
*
* IMPORTANT: Copy and paste the libssl-3-x64.dll, libcrypto-3-x64.dll, mysqlcppconn-10-vs14.dll, mysqlcppconnx-2-vs14.dll and the .pdb too
*/
using namespace std;
int main() {
    sql::Driver* driver = sql::mysql::get_driver_instance();

    try {
        sql::Connection* connection = driver->connect("tcp://10.242.198.254:3306", "test", "toor");
        cout << "Connection Sucess!\n";
        connection->setSchema("test");
        sql::Statement* stmt((*connection).createStatement());
        sql::ResultSet* res(
            (*stmt).executeQuery("SELECT * FROM test.inv;")
        );


        while ((*res).next())
        {
            std::cout << (*res).getString(5) << "\n";
        }

        delete stmt;
        delete res;
        delete connection;
    }
    catch (const sql::SQLException& error) {
        cerr << "SQL error: " << error.what() << '\n';
    }
    catch (const std::exception& error) {
        cerr << "Other error: " << error.what() << '\n';
    }

}