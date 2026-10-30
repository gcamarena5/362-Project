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
