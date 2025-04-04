# Library_Management

To connect MySQL to Dev C++, you'll need to set up the MySQL Connector/C++ and configure your Dev C++ environment to link with it. Here are the steps to achieve this:
1. Install MySQL Server
2. Install Dev C++
Steps to Add the MySQL Library Path in Dev C++
Open Dev C++
Launch Dev C++ on your system.
1. Go to Compiler Options
2. Click on Tools in the top menu.

Select Compiler Options from the dropdown.

1. Add the Library Path
2. In the Compiler Options window, go to the Directories tab.
3. Choose Libraries (this is where you add library paths).
4. Click on Add (C:\Program Files\MySQL\MySQL Server 8.0\lib).

Navigate to Include Directories
1. Click on the Add button (or simply type the path).
2. Add the following paths one by one:

C:\Program Files\MySQL\MySQL Server 8.0\include
C:\Program Files\MySQL\MySQL Server 8.0\include\mysql

In the Linker section, find the Add the following commands when calling the linker box.

Add the following line: -lmysql

copy this file in the the main project directory : libmysql.dll (from mysql>mysql server>lib>libmysql.dll)
