// Name: Ba Dieu, Justin Lai, Greg Camarena, Liliana Valdez
// Date:9/24/26
 
#include <iostream>
#include <mysql/jdbc.h>
#include "demo.h"
// New Update:
/*
* For SQL builing, future reference, get the debug binaries instead of installation for VS studio coding
* Linker - General - "C:\...\mysql-connector-c++-26.7.0-winx64\lib64\debug"
* Linker - Input - "C:\...\mysql-connector-c++-26.7.0-winx64\lib64\debug\vs14\mysqlcppconn.lib"
* C/C++ - General - "C:\...\Program Files\MySQL\MySQL Connector C++ 26.7\include"
*
* IMPORTANT: Copy and paste the libssl-3-x64.dll, libcrypto-3-x64.dll, mysqlcppconn-10-vs14.dll, mysqlcppconnx-2-vs14.dll and the .pdb too
*/
using namespace std;

int main() {
    run();
    return 0;
}