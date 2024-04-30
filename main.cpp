#include <iostream>
#include "menu.h"

int main()
{
    printLogo();
    bool isAdmin = login();
    printMenu(true);
    return 0;
}