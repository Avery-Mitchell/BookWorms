#include <iostream>
#include <string.h>
#include <mysql/mysql.h>
#include "menu.h"
#include "database.h"
using namespace std;

void printLogo()
{
    cout << "=============================================================\n";
    cout << "______  _____  _____ _   ___    _  ______________  ___ _____ \n";
    cout << "| ___ \\|  _  ||  _  | | / / |  | ||  _  | ___ \\  \\/  |/  ___|\n";
    cout << "| |_/ /| | | || | | | |/ /| |  | || | | | |_/ / .  . |\\ `--. \n";
    cout << "| ___ \\| | | || | | |    \\| |/\\| || | | |    /| |\\/| | `--. \\\n";
    cout << "| |_/ /\\ \\_/ /\\ \\_/ / |\\  \\  /\\  /\\ \\_/ / |\\ \\| |  | |/\\__/ /\n";
    cout << "\\____/  \\___/  \\___/\\_| \\_/\\/  \\/  \\___/\\_| \\_\\_|  |_/\\____/ \n";
    cout << "LIBRARY DATABASE SOLUTION\n";
    cout << "=============================================================\n" << std::endl;

}

void collectLogin(std::string& username, std::string& password, bool& isAdmin)
{
    std::string tAdmin = "Z";
    isAdmin = false;
    std::cout << "ENTER FIRST AND LAST NAME (e.x. John Doe): ";
    std::getline(std::cin, username);
    std::cout << "ENTER PASSWORD (case sensitive): ";
    std::getline(std::cin, password);
    std::cout << "ARE YOU A LIBRARIAN? [Y/N]: ";
    std::getline(std::cin, tAdmin);
    while(tAdmin != "Y" && tAdmin != "N")
    {
        std::cout << "ARE YOU A LIBRARIAN? [Y/N]: ";
        std::cin >> tAdmin;
    }
    if(tAdmin == "Y")
    {
        isAdmin = true;
    }
}

void printMenu(MYSQL *conn, std::string username, std::string userid, bool isAdmin)
{
    cout << endl;
    cout << "===============================\n";
    cout << "     __  __________   ____  __\n";
    cout << "    /  |/  / ____/ | / / / / /\n";
    cout << "   / /|_/ / __/ /  |/ / / / / \n";
    cout << "  / /  / / /___/ /|  / /_/ /  \n";
    cout << " /_/  /_/_____/_/ |_/\\____/  \n";
    cout << "===============================\n\n";

    cout << "1.  QUIT\n";
    cout << "2.  Search Books\n";
    cout << "3.  Add Review\n";
    cout << "4.  View Borrow History\n";
    cout << "5.  Manage Account\n\n";

    if(isAdmin){
        cout << "LIBRARIAN FUNCTIONS:\n";
        cout << "6.  Check Out Book\n";
        cout << "7.  Check In Book\n";
        cout << "8.  Add Book\n";
        cout << "9.  Edit Book\n";
        cout << "10. Remove Book\n";
        cout << "11. Add New Acount\n";
        cout << "12. Remove Account\n\n";
    }

    int option;
    std::cin.clear();
    std::cout << "Enter Option: ";
    std::cin >> option;
    std::cin.clear();
    switch(option){
        case 1: // Quit
            {
                std::cout << "BYE!" << std::endl;
                exit(1);
                break;
            }
        case 2: // Search Books
            {
                searchBooks(conn);
                break;
            }
        case 3: // Add Review
            {
                std::string reviewISBN;
                std::cout << "Enter ISBN of the book to review: ";
                std::cin >> reviewISBN;
                addReview(conn, reviewISBN, username);
                break;
            }
        case 4: // View Borrow History
            {
                viewBorrowHistory(conn, userid);
                break;
            }
        case 5: // Manage Account
            {
                manageAccount(conn, isAdmin, userid);
                break;
            }
        case 6: // Check Out Book
            {
                checkOut(conn);
                break;
            }
        case 7: // Check In Book
            {
                checkIn(conn);
                break;
            }
        case 8: // Add Book
            {
                addBooks(conn);
                break;
            }
        case 9: // Edit Book
            {
                editBooks(conn);
                break;
            }
        case 10: // Remove Book
            {
                removeBooks(conn);
                break;
            }
        case 11: // Add new Account
            {
                addNewUser(conn);
                break;
            }
        case 12: // Remove Account
            {
                break;
            }
        default:
            {
                std::cout << "Select Valid Option";
                break;
            }
    }
}
