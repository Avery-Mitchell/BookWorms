#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>

//Checks to see if the username information is valid
bool login(MYSQL *conn, bool& admin, std::string& userid, std::string username, std::string password);
std::string userID(MYSQL *conn, std::string username);
bool searchName(MYSQL *conn, std::string title);
bool searchISBN(MYSQL *conn, std::string ISBN);
void searchBooks(MYSQL *conn);
void addReview(MYSQL *conn, std::string ISBN, std::string username);
void viewBorrowHistory(MYSQL *conn, std::string username);
void manageAccount(MYSQL *conn, bool admin, std::string username);
void checkIn(MYSQL *conn);

#endif
