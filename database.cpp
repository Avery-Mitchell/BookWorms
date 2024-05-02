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
