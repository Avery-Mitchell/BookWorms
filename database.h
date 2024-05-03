#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>

//Checks to see if the username information is valid
bool login(MYSQL *conn, bool& admin, std::string username, std::string password);
bool searchName(MYSQL *conn, std::string title);
bool searchISBN(MYSQL *conn, std::string ISBN);
void searchBooks(MYSQL *conn);
void addReview(MYSQL *conn, std::string ISBN, std::string user_id);

#endif
