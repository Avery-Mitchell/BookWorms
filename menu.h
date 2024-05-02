#ifndef MENU_H
#define MENU_H

void printLogo();
void collectLogin(std::string& username, std::string& password, bool& isAdmin);
void printMenu(bool isAdmin);

#endif