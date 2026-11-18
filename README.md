# Title: Group 5 Warehouse 

## Description: A warehouse program that uses client side C++ to interact with an AWS RDS server

# Table of contents:
### Project Description
### Tech Stack  
### Features 
### How to use it

# A guide: 
Before Running
-
Because the binary files are larger than 100MB, a `Copy of debug.7z` has been made for you as an all-in-one clone. Before running the `.sln`, please unzip or extract the file.

Here are some steps to ensure you are in the right direction: 

1. Unzip or Extract `Copy of debug.7z`
   -   `Copy of debug.7z` is located in `MySQL/mysql-connector-c++-26.7.0-debug/lib64/Copy of debug.7z`
2. Make sure the `debug` folder from `Copy of debug.7z` is in the correct directory:

- Your directory should now look like this:
   - Ex: `MySQL\mysql-connector-c++-26.7.0-debug\lib64\debug\`
   
In that folder, you should see the `vs14` folder, some `.dll` files, and `.pdb` files.

The following are `NOT` valid locations:
  - Ex: `MySQL\mysql-connector-c++-26.7.0-debug\lib64\Copy of debug\`
  - Ex: `MySQL\mysql-connector-c++-26.7.0-debug\lib64\Copy of debug\debug\`

If you have the following directory locations, move the following `debug` folder to `lib64`.

## AWS EC2 Development Environment

### Environment Setup
- Operating System: Amazon Linux 2023
- Development Environment: AWS EC2
- Database: Shared Amazon RDS MySQL
- Database Port: 3306

### Database Connectivity
- Configured personal AWS EC2 development environment.
- Installed the MariaDB-compatible MySQL command-line client.
- Attempted connectivity testing with the shared RDS database.

### Development Progress
- Prepared the environment for inventory dashboard development.
- Documented AWS environment setup and database connectivity troubleshooting.
- Preparing infrastructure for browser-based inventory dashboard development.

## Project Contributors

### Liliana Valdez
**Role:** AWS EC2 Environment Setup & Database Connectivity

**Contributions:**
- Configured personal AWS EC2 development environment using Amazon Linux 2023.
- Identified and configured access to the shared Group 5 Amazon RDS environment.
- Installed the MariaDB-compatible MySQL command-line client.
- Documented environment setup and database connectivity procedures.
- Investigated database connectivity issues.
- Planned infrastructure for browser-based inventory dashboard development.


# Project description:
## This is an automotive warehouse inventory program that solves the issue of using paper trails in regards to inventory. It communicates with a hosted database, making it accessible almost anywhere. It solves the issue of having locked down access to said database. 

# How to use: 
## Before anything, make sure the AWS server is up and running. Connect and you will be prompted with a menu.
<img width="902" height="286" alt="image" src="https://github.com/user-attachments/assets/8979c59c-f586-4852-a8ea-5f13a04c7cf1" />

Hit 1 to view inventory

<img width="822" height="85" alt="image" src="https://github.com/user-attachments/assets/1d5e987d-e87f-4d78-ab5c-2251b3b581e8" />

Hit 2 to add items. Add in various information



<img width="752" height="307" alt="image" src="https://github.com/user-attachments/assets/b5c0dfdc-8398-4855-bc2a-c7fd0e29f104" />

Hit 3 to delete 

<img width="802" height="142" alt="image" src="https://github.com/user-attachments/assets/8e076c13-1eb0-46f8-ae48-aacc237673a7" />

Hit 4 to exit





# Tech Stack:
## This uses C++ for the client side program. The connector is "MySqLConnector". Our lintr is Clangtidy. Our database is hosted using AWS. 

## Features:
## This program features the ability to add, delete, edit, and view an inventory database. 

## Directory structure: 
## Project Structure

```text
.
|-- MySQL
|   |-- Database.cpp
|   |-- Database.h
|   |-- Demo.h
|   |-- Input.cpp
|   |-- Input.h
|   |-- Item.h
|   |-- Menu.h
|   |-- MySQL.vcxproj
|   |-- MySQL.vcxproj.filters
|   |-- X64
|   |   `-- debug
|   |       |-- libcrypto-3-x64.dll
|   |       |-- libssl-3-x64.dll
|   |       |-- mysqlcppconn-10-vs14.dll
|   |       |-- mysqlcppconn-10-vs14.pdb
|   |       |-- mysqlcppconnx-2-vs14.dll
|   |       `-- mysqlcppconnx-2-vs14.pdb
|   |-- env
|   |   `-- x64-debug
|   |       |-- MySQL.exe
|   |       |-- libcrypto-3-x64.dll
|   |       |-- libssl-3-x64.dll
|   |       |-- mysqlcppconn-10-vs14.dll
|   |       `-- mysqlcppconnx-2-vs14.dll
|   |-- main.cpp
|   `-- mysql-connector-c++-26.7.0-debug
|       |-- CONTRIBUTING.md
|       |-- INFO_BIN
|       |-- INFO_SRC
|       |-- LICENSE.txt
|       |-- README.txt
|       |-- include
|       |   |-- jdbc
|       |   |   |-- cppconn
|       |   |   |   |-- build_config.h
|       |   |   |   |-- callback.h
|       |   |   |   |-- config.h
|       |   |   |   |-- connection.h
|       |   |   |   |-- datatype.h
|       |   |   |   |-- driver.h
|       |   |   |   |-- exception.h
|       |   |   |   |-- metadata.h
|       |   |   |   |-- parameter_metadata.h
|       |   |   |   |-- prepared_statement.h
|       |   |   |   |-- resultset.h
|       |   |   |   |-- resultset_metadata.h
|       |   |   |   |-- sqlstring.h
|       |   |   |   |-- statement.h
|       |   |   |   |-- variant.h
|       |   |   |   |-- version_info.h
|       |   |   |   `-- warning.h
|       |   |   |-- mysql_connection.h
|       |   |   |-- mysql_driver.h
|       |   |   `-- mysql_error.h
|       |   |-- mysql
|       |   |   `-- jdbc.h
|       |   `-- mysqlx
|       |       |-- common
|       |       |   |-- api.h
|       |       |   |-- error.h
|       |       |   |-- op_if.h
|       |       |   |-- settings.h
|       |       |   |-- util.h
|       |       |   `-- value.h
|       |       |-- common.h
|       |       |-- common_constants.h
|       |       |-- devapi
|       |       |   |-- collations.h
|       |       |   |-- collection_crud.h
|       |       |   |-- common.h
|       |       |   |-- crud.h
|       |       |   |-- detail
|       |       |   |   |-- crud.h
|       |       |   |   |-- error.h
|       |       |   |   |-- result.h
|       |       |   |   |-- row.h
|       |       |   |   |-- session.h
|       |       |   |   `-- settings.h
|       |       |   |-- document.h
|       |       |   |-- error.h
|       |       |   |-- executable.h
|       |       |   |-- mysql_charsets.h
|       |       |   |-- mysql_collations.h
|       |       |   |-- result.h
|       |       |   |-- row.h
|       |       |   |-- settings.h
|       |       |   `-- table_crud.h
|       |       |-- version_info.h
|       |       |-- xapi.h
|       |       `-- xdevapi.h
|       |-- lib64
|       |   |-- Copy of debug.7z
|       |   |-- debug
|       |   |   |-- mysqlcppconn-10-vs14.dll
|       |   |   |-- mysqlcppconn-10-vs14.pdb
|       |   |   |-- mysqlcppconnx-2-vs14.dll
|       |   |   |-- mysqlcppconnx-2-vs14.pdb
|       |   |   `-- vs14
|       |   |       |-- mysqlcppconn-static.lib
|       |   |       |-- mysqlcppconn.lib
|       |   |       |-- mysqlcppconnx-static.lib
|       |   |       `-- mysqlcppconnx.lib
|       |   |-- libcrypto-3-x64.dll
|       |   |-- libssl-3-x64.dll
|       |   |-- plugin
|       |   |   |-- authentication_kerberos_client.dll
|       |   |   |-- authentication_ldap_sasl_client.dll
|       |   |   |-- authentication_oci_client.dll
|       |   |   |-- authentication_openid_connect_client.dll
|       |   |   |-- authentication_webauthn_client.dll
|       |   |   `-- mysql_native_password.dll
|       |   `-- vs14
|       |       |-- libcrypto.lib
|       |       `-- libssl.lib
|       |-- mysql-concpp-config-version.cmake
|       `-- mysql-concpp-config.cmake
|-- MySQL.sln
|-- README.md
|-- test.cpp
`-- tree.txt

19 directories, 102 files
```
