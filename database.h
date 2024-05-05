#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>

//Checks to see if the username information is valid
bool login(MYSQL *conn, bool& admin, std::string& userid, std::string username, std::string password);
std::string userID(MYSQL *conn, const std::string& username);
int getMaxID(MYSQL *conn, std::string tableName, std::string idColumnName);
bool searchName(MYSQL *conn, std::string title);
bool searchISBN(MYSQL *conn, std::string ISBN);
void searchBooks(MYSQL *conn);
void addReview(MYSQL *conn, std::string ISBN, std::string username);
void viewBorrowHistory(MYSQL *conn, std::string username);
void manageAccount(MYSQL *conn, bool admin, std::string username);
void checkOut(MYSQL *conn);
void checkIn(MYSQL *conn);
void addBooks(MYSQL *conn);
void editBooks(MYSQL *conn);
void removeBooks(MYSQL *conn);
void addNewUser(MYSQL *conn);
void removeAccounts(MYSQL *conn);

#endif
