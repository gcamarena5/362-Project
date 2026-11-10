# MySQL
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
