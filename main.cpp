/*
    NAMES:  Lauren Higgins
            Jerry Li
            Avery Mitchell
            Armarion Parnell
    GROUP: Book Worms
    ASSIGNMENT: Project Phase III

*/

#include <iostream>
#include "menu.h"

int main()
{
    printLogo();
    bool isAdmin = login();
    printMenu(true);
    return 0;
}