/*
    NAMES:  Lauren Higgins
            Jerry Li
            Avery Mitchell
            Armarion Parnell
    GROUP: Book Worms
    ASSIGNMENT: Project Phase III

*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include "menu.h"
#include "database.h"

int main()
{
    MYSQL *conn;    //MySQL Connection Object
    MYSQL_RES *res; //Result of a Query
    MYSQL_ROW row;  //Row in the Database 

    //Initializes the connection object
    conn = mysql_init(NULL);
    if(conn == NULL){
        std::cout << "ERROR INITIALIZING MYSQL CONNECTION\n";
        mysql_close(conn);
        exit(1);
    }

    //Connects to the database
    //mysql_real_connect parameters:   mysql object, hostname, user, password, database name, port, unix socket, client flag
    //You need to run a local instance of the database, I've been using MySQL Workbench - Avery
    if(mysql_real_connect(conn, "localhost", "root", "2016VWJetta!", "BOOKWORMS", 0, NULL, 0) == NULL){
        std::cout << "ERROR CONNECTING TO DATABASE\n";
        mysql_close(conn);
        exit(1);
    }

    printLogo();

    bool isAdmin = false;
    std::string username, password;
    int option;
    collectLogin(username, password, isAdmin);
    while(!login(conn, isAdmin, username, password))
    {
        std::cout << "INCORRECT, TRY AGAIN\n";
        collectLogin(username, password, isAdmin);
        login(conn, isAdmin, username, password);
    }
    if(login(conn, isAdmin, username, password))
    {
        std::cout << "LOGIN SUCCESSFUL\n";
    }

    while(true)
    {
        printMenu(isAdmin);
        std::cin >> option;
        switch(option){
            case 1: // Quit
                std::cout << "BYE!";
                exit(1);
                break;
            case 2: // Search Books
                break;
            case 3: // Add Review
                break;
            case 4: // View Borrow History
                break;
            case 5: // Manage Account
                break;
            case 6: // Check Out Book
                break;
            case 7: // Check In Book
                break;
            case 8: // Add Book
                break;
            case 9: // Edit Book
                break;
            case 10: // Remove Book
                break;
            case 11: // Add new Account
                break;
            case 12: // Remove Account
                break;
        }
    }
    return 0;
}