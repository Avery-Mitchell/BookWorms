#include <iostream>
#include <cstring>
#include "database.h"

bool login(MYSQL *conn, bool& admin, std::string username, std::string password)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query1[1000];
    char query2[1000];

    sprintf(query1, "SELECT * FROM LIBRARIAN WHERE e_name='%s' AND e_pass='%s'", username.c_str(), password.c_str());
    sprintf(query2, "SELECT * FROM PATRON WHERE user_name='%s' AND user_pass='%s'", username.c_str(), password.c_str());

    if(admin)
    {
        if(mysql_query(conn, query1))
        {
            std::cout << "ERROR QUERYING DATABASE\n";
            return false;
        }
        res = mysql_store_result(conn);
        if((row = mysql_fetch_row(res)) != NULL)
        {
            mysql_free_result(res);
            return true;
        }
        else
        {
            mysql_free_result(res);
            return false;
        }
    }
    else
    {
        if(mysql_query(conn, query2))
        {
            std::cout << "ERROR QUERYING DATABASE\n";
            return false;
        }
        res = mysql_store_result(conn);
        if((row = mysql_fetch_row(res)) != NULL)
        {
            mysql_free_result(res);
            return true;
        }
        else
        {
            mysql_free_result(res);
            return false;
        }
    }
}

bool searchName(MYSQL *conn, std::string title)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1000];

    sprintf(query, "SELECT * FROM BOOK WHERE title='%s'", title.c_str());

    if(mysql_query(conn, query))
    {
        std::cout << "ERROR QUERYING DATABASE\n";
        return false;
    }

    res = mysql_store_result(conn);
    if(res)
    {
        if((row = mysql_fetch_row(res)) != NULL)
        {
           std::cout << "Title: " << row[1];
           std::cout << "\nAuthor: " << row[2];
           std::cout << "\nPublished Date: " << row[3];
           std::cout << "\nPage Count: " << row[4] << "pages";
           std::cout << "\nISBN: " << row[0];
           std::cout << "\nAvailability: " << row[5];
           std::cout << "\nRating: " << row[6];

           mysql_free_result(res);
           return true;
        }
        mysql_free_result(res);
    }
    else
    {
        std::cout << "BOOK NOT FOUND :(\n";
        return false;
    }
    return false;
}

bool searchISBN(MYSQL *conn, std::string ISBN)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1000];

    sprintf(query, "SELECT * FROM BOOK WHERE ISBN='%s'", ISBN.c_str());

    if(mysql_query(conn, query))
    {
        std::cout << "ERROR QUERYING DATABASE\n";
        return false;
    }

    res = mysql_store_result(conn);
    if(res)
    {
        if((row = mysql_fetch_row(res)) != NULL)
        {
           std::cout << "Title: " << row[1];
           std::cout << "\nAuthor: " << row[2];
           std::cout << "\nPublished Date: " << row[3];
           std::cout << "\nPage Count: " << row[4] << "pages";
           std::cout << "\nISBN: " << row[0];
           std::cout << "\nAvailability: " << row[5];
           std::cout << "\nRating: " << row[6];

           mysql_free_result(res);
           return true;
        }
        mysql_free_result(res);
    }
    else
    {
        std::cout << "BOOK NOT FOUND :(\n";
        return false;
    }
    return false;
}

void searchBooks(MYSQL *conn)
{
    char temp;
    std::string title;
    std::string ISBN;
    std::cout << "Search by Title or ISBN [T/I]: ";
    std::cin >> temp;
    while(temp != 'T' && temp != 'I')
    {
        std::cout << "Search by Title or ISBN [T/I]: ";
        std::cin >> temp;
    }
    if(temp == 'T')
    {
        std::cout << "Enter Title: ";
        std::cin >> title;
        searchName(conn, title);
    }
    else
    {
        std::cout << "Enter ISBN: ";
        std::cin >> ISBN;
        searchISBN(conn, ISBN);
    }
}