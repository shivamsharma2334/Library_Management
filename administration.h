#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

#include <iostream>
#include <mysql.h>
#include <windows.h>
#include <iomanip>
#include <mysqld_error.h>

using namespace std;

const char *HOST = "localhost";
const char *USER = "root";
const char *PASSWORD = "0000";
const int PORT = 3306;
const char *DATABASE = "DIATM_LIB";


void printdata(MYSQL *conn, const string &TABLE)
{
    string query = "SELECT * FROM " + TABLE;
    if (mysql_query(conn, query.c_str()))
    {
        cerr << "Query Error: " << mysql_error(conn) << endl;
        return;
    }
    MYSQL_RES *res = mysql_store_result(conn);
    if (!res)
    {
        cerr << "No records found: " << mysql_error(conn) << endl;
        return;
    }
    int num_fields = mysql_num_fields(res);
    MYSQL_FIELD *field;

    cout << left << endl;
    while ((field = mysql_fetch_field(res)))
    {
        cout << setw(18) << field->name;
    }
    cout << endl
         << string(num_fields * 15, '-') << endl;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            cout << setw(15) << (row[i] ? row[i] : "NULL") << " | ";
        }
        cout << endl;
    }
    mysql_free_result(res);
}

class Admin
{
private:
    const string TABLE = "administration";

protected:
    MYSQL *conn;

public:
    Admin()
    {
        conn = mysql_init(NULL);
        if (!conn)
        {
            cerr << "MySQL Initialization Error" << endl;
            exit(1);
        }
        if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0))
        {
            cerr << "Connection Error: " << mysql_error(conn) << endl;
            exit(1);
        }
    }
    ~Admin()
    {
        mysql_close(conn);
    }

    void displayData();
    void insertData();
    bool validateUser();
    void deletedata();
};

bool Admin::validateUser()
{
    string mail, Pass;
    cout << "Enter Admin credentials to edit the table..." << endl;
    cout << "Enter Email-ID: ";
    cin >> mail;
    cout << "Enter Password: ";
    cin >> Pass;
    string query = "SELECT EMAIL, PASSWORD FROM " + TABLE + " WHERE EMAIL = '" + mail + "' AND PASSWORD ='" + Pass + "'";
    if (mysql_query(conn, query.c_str()))
    {
        cerr << "Query Error: " << mysql_error(conn) << endl;
        return false;
    }
    else
    {
        MYSQL_RES *res = mysql_store_result(conn);
        if (res)
        {
            int row = mysql_num_rows(res);
            if (row == 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

void Admin::insertData()
{
    string id, name, email, pass;
    cout << "\nEnter the data for the administration table" << endl;
    cout << "Enter ID: (T001) ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Email: ";
    getline(cin, email);
    cout << "Enter Password: ";
    cin >> pass;

    string query = "INSERT INTO " + TABLE + " (T_ID, NAME, EMAIL, PASSWORD) VALUES ('" + id + "', '" + name + "', '" + email + "', '" + pass + "')";
    if (mysql_query(conn, query.c_str()))
    {
        cerr << "Insert Error: " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Data inserted successfully!" << endl;
    }
    Sleep(1000);
}

void Admin::displayData()
{
    printdata(conn, TABLE);
}

void Admin::deletedata()
{
    string id;
    cout << "\nEnter the ID (T001) of the record to delete: ";
    cin >> id;
    string query = "DELETE FROM " + TABLE + " WHERE T_ID = '" + id + "'";

    if (mysql_query(conn, query.c_str()))
    {
        cerr << "Delete Error: " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Record with ID " << id << " deleted successfully!" << endl;
    }

    Sleep(1000);
}

class books : public virtual Admin
{
private:
    const string TABLE = "books";

public:
    void searchbook();
    void displaybook();
    void addbook();
};
void books::addbook()
{
    string id, name, author, isbn;
    cout << "\nEnter the data for the books table" << endl;
    cout << "Enter ID: (B001) ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter author: ";
    getline(cin, author);
    cout << "Enter ISBN: ";
    cin >> isbn;

    string query = "INSERT INTO " + TABLE + " (Book_id, Name, Author, ISBN) VALUES ('" + id + "', '" + name + "', '" + author + "', '" + isbn + "')";
    if (mysql_query(conn, query.c_str()))
    {
        cerr << "Insert Error: " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Data inserted successfully!" << endl;
    }
    Sleep(1000);
}
void books::displaybook()
{
    printdata(conn, TABLE);
}

void books::searchbook()
{
    string name, query;
    cout << "Enter the book name: ";
    getline(cin, name);

    query = "SELECT * FROM " + TABLE + " WHERE Name = '" + name + "'";

    if (mysql_query(conn, query.c_str()))
    {
        cerr << "Error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res)
    {
        cout << "No records found." << endl;
        return;
    }

    int num_fields = mysql_num_fields(res);
    MYSQL_FIELD *field;

    cout << left;
    while ((field = mysql_fetch_field(res)))
    {
        cout << setw(18) << field->name;
    }
    cout << endl
         << string(num_fields * 15, '-') << endl;

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            cout << setw(15) << (row[i] ? row[i] : "NULL");
        }
        cout << endl;
    }

    mysql_free_result(res);
}

class available : virtual public Admin
{
private:
    const string TABLE = "available";

public:
    void availablebook();
};

void available ::availablebook()
{
    printdata(conn, TABLE);
}

class checkout : virtual public Admin
{
private:
    const string TABLE = "checkout";

public:
    void dispalycheckout()
    {
        printdata(conn, TABLE);
    }
    void checkoutbook();
};

void checkout::checkoutbook()
{
    string name, id;
    char date;
    cout << "\nEnter the data for checkout" << endl;
    cout << "Enter Book_name ";
    getline(cin, name);
    cout << "Enter User_ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Due_Date: ";
    cin >> date;

    string query = "INSERT INTO " + TABLE + " (Book_name,User_ID, Due_Date) VALUES ('" + name + "', '" + id + "', '" + date + "')";
    if (mysql_query(conn, query.c_str()))
    {
        cerr << "Insert Error: " << mysql_error(conn) << endl;
        Sleep(2000);
    }
    else
    {
        cout << "Data inserted successfully!" << endl;
    }
    Sleep(1000);
}

class returnbook : virtual public Admin
{
private:
    const string TABLE = "return_book";

public:
    void dispalyreturn()
    {
        printdata(conn, TABLE);
    }
    void returnboo(void);
};

void returnbook::returnboo()
{
    string id;
    cout << "\nEnter the ID (T001) of the record to delete: ";
    cin >> id;
    string query = "DELETE FROM " + TABLE + " WHERE T_ID = '" + id + "'";

    if (mysql_query(conn, query.c_str()))
    {
        cerr << "Delete Error: " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Record with ID " << id << " deleted successfully!" << endl;
    }

    Sleep(1000);
}

#endif
