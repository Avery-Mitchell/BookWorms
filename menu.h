#ifndef MENU_H
#define MENU_H

void printLogo();
void collectLogin(std::string& username, std::string& password);
void printMenu(MYSQL *conn, std::string username, std::string userid, bool isAdmin);

#endif