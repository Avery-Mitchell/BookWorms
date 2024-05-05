#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>

//Checks to see if the username information is valid
bool login(MYSQL *conn, bool& admin, std::string& userid, std::string username, std::string password);
//Returns a user's userid based on their name
//Only works with patrons, not
std::string userID(MYSQL *conn, const std::string& username);
//Returns the maximum ID value, used to ensure no duplicate primary keys
int getMaxID(MYSQL *conn, std::string tableName, std::string idColumnName);
//Searches for a book based on its name
bool searchName(MYSQL *conn, std::string title);
//Searches for a book based on its ISBN
bool searchISBN(MYSQL *conn, std::string ISBN);
//Calls searchName or searchISBN, allows users to search for books
void searchBooks(MYSQL *conn);
//Allows users to add reviews to books
void addReview(MYSQL *conn, std::string ISBN, std::string username);
//Allows users to see their borrow history
void viewBorrowHistory(MYSQL *conn, std::string userid);
//Allows users to change their password
void manageAccount(MYSQL *conn, bool admin, std::string userid);
//Allows librarians to check out books
void checkOut(MYSQL *conn);
//Allows librarians to check in books
void checkIn(MYSQL *conn);
//Allows librarians to add books to the database
void addBooks(MYSQL *conn);
//Allows librarians to edit information about books
void editBooks(MYSQL *conn);
//Allows librarians tp remove books from the library
void removeBooks(MYSQL *conn);
//Allows librarians to add new users to the database
void addNewUser(MYSQL *conn);
//Allows librarians to remove accounts from the database
void removeAccounts(MYSQL *conn);

#endif
