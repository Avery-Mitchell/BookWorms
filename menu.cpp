#include <iostream>
#include "menu.h"
using namespace std;

void printLogo()
{
   cout << "\n______  _____  _____ _   ___    _  ______________  ___ _____ \n";
   cout << "| ___ \\|  _  ||  _  | | / / |  | ||  _  | ___ \\  \\/  |/  ___|\n";
   cout << "| |_/ /| | | || | | | |/ /| |  | || | | | |_/ / .  . |\\ `--. \n";
   cout << "| ___ \\| | | || | | |    \\| |/\\| || | | |    /| |\\/| | `--. \\\n";
   cout << "| |_/ /\\ \\_/ /\\ \\_/ / |\\  \\  /\\  /\\ \\_/ / |\\ \\| |  | |/\\__/ /\n";
   cout << "\\____/  \\___/  \\___/\\_| \\_/\\/  \\/  \\___/\\_| \\_\\_|  |_/\\____/ \n";
   cout << "LIBRARY DATABASE SOLUTION\n" << endl;
   
}

bool login()
{
    string username, password;
    cout << "ENTER USERNAME: ";
    cin >> username;
    cout << "ENTER PASSWORD: ";
    cin >> password;

    return true;
}

void printMenu(bool isAdmin)
{
    cout << endl;
    cout << "    __  __________   ____  __\n";
    cout << "   /  |/  / ____/ | / / / / /\n";
    cout << "  / /|_/ / __/ /  |/ / / / / \n";
    cout << " / /  / / /___/ /|  / /_/ /  \n";
    cout << "/_/  /_/_____/_/ |_/\\____/  \n";
    cout << "=============================\n\n";

    cout << "1.  Search Books\n";
    cout << "2.  Add Review\n";
    cout << "3.  View Borrow History\n";
    cout << "4.  Manage Account\n\n";

    if(isAdmin){
        cout << "LIBRARIAN FUNCTIONS:\n";
        cout << "5.  Check Out Book\n";
        cout << "6.  Check In Book\n";
        cout << "7.  Add Book\n";
        cout << "8.  Edit Book\n";
        cout << "9.  Remove Book\n";
        cout << "10. Add New Acount\n";
        cout << "11. Remove Account\n\n";
    }
}