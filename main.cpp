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
    std::string username, password, userid;
    int option;
    collectLogin(username, password);
    while(!login(conn, isAdmin, userid, username, password))
    {
        std::cout << "INCORRECT, TRY AGAIN\n";
        collectLogin(username, password);
        login(conn, isAdmin, userid, username, password);
    }
    if(login(conn, isAdmin, userid, username, password))
    {
        std::cout << "LOGIN SUCCESSFUL\n";
    }

    while(true)
    {
        std::string temp;
        printMenu(conn, username, userid, isAdmin);
        //std::cin.ignore();
        std::cout << "\n\nPress Any Key to Continue ";
        std::getline(std::cin, temp);
        std::cout << std::endl;
    }

    return 0;
}
