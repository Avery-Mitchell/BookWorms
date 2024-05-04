#include <iostream>
#include <cstring>
#include "database.h"

// Login to the database
bool login(MYSQL *conn, bool& admin, std::string& userid, std::string username, std::string password)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query1[1000];
    char query2[1000];

    sprintf(query1, "SELECT e_id FROM LIBRARIAN WHERE e_name='%s' AND e_pass='%s'", username.c_str(), password.c_str());
    sprintf(query2, "SELECT user_id FROM PATRON WHERE user_name='%s' AND user_pass='%s'", username.c_str(), password.c_str());

    if(admin)
    {
        if(mysql_query(conn, query1))
        {
            std::cout << "ERROR QUERYING DATABASE\n";
            return false;
        }
        res = mysql_store_result(conn);
        if((row = mysql_fetch_row(res)) != NULL)
        {
            userid = row[0];
            mysql_free_result(res);
            return true;
        }
        else
        {
            mysql_free_result(res);
            return false;
        }
    }
    else
    {
        if(mysql_query(conn, query2))
        {
            std::cout << "ERROR QUERYING DATABASE\n";
            return false;
        }
        res = mysql_store_result(conn);
        if((row = mysql_fetch_row(res)) != NULL)
        {
            userid = row[0];
            mysql_free_result(res);
            return true;
        }
        else
        {
            mysql_free_result(res);
            return false;
        }
    }
}

// gets userid from their username
std::string userID(MYSQL *conn, std::string username)
{
    std::string userid, query;
    MYSQL_RES *res;
    MYSQL_ROW row;
    query = "SELECT user_id FROM PATRON WHERE user_name = '" + username + "'";
    while(mysql_query(conn, query.c_str()))
    {
        std::cout << "No patron with that name";
        std::cout << "What is the patron's name (e.x. John Doe): ";
        std::cin >> username;
        query = "SELECT user_id FROM PATRON WHERE user_name = '" + username + "'";
    }

    res = mysql_store_result(conn);
    if((row = mysql_fetch_row(res)) != NULL)
        {
            userid = row[0];
            mysql_free_result(res);
        }

    return userid;
}

int getMaxID(MYSQL *conn, std::string tableName, std::string idColumnName) {
    std::string query = "SELECT MAX(" + idColumnName + ") FROM " + tableName;
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Error getting max ID: " << mysql_error(conn) << std::endl;
        return -1; // Error condition
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    int maxID = (row && row[0]) ? std::stoi(row[0]) : 0;
    mysql_free_result(result);
    return maxID;
}

// SEARCHES FOR A BOOK BY ITS NAME
bool searchName(MYSQL *conn, std::string title)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1000];

    sprintf(query, "SELECT * FROM BOOK WHERE title='%s'", title.c_str());

    if(mysql_query(conn, query))
    {
        std::cout << "ERROR QUERYING DATABASE\n";
        return false;
    }

    res = mysql_store_result(conn);
    if(res)
    {
        if((row = mysql_fetch_row(res)) != NULL)
        {
           std::cout << "Title: " << row[1];
           std::cout << "\nAuthor: " << row[2];
           std::cout << "\nPublished Date: " << row[3];
           std::cout << "\nPage Count: " << row[4] << "pages";
           std::cout << "\nISBN: " << row[0];
           std::cout << "\nAvailability: " << row[5];
           std::cout << "\nRating: " << row[6];

           mysql_free_result(res);
           return true;
        }
        mysql_free_result(res);
    }
    else
    {
        std::cout << "BOOK NOT FOUND :(\n";
        return false;
    }
    return false;
}

bool searchISBN(MYSQL *conn, std::string ISBN)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1000];

    sprintf(query, "SELECT * FROM BOOK WHERE ISBN='%s'", ISBN.c_str());

    if(mysql_query(conn, query))
    {
        std::cout << "ERROR QUERYING DATABASE\n";
        return false;
    }

    res = mysql_store_result(conn);
    if(res)
    {
        if((row = mysql_fetch_row(res)) != NULL)
        {
           std::cout << "Title: " << row[1];
           std::cout << "\nAuthor: " << row[2];
           std::cout << "\nPublished Date: " << row[3];
           std::cout << "\nPage Count: " << row[4] << "pages";
           std::cout << "\nISBN: " << row[0];
           std::cout << "\nAvailability: " << row[5];
           std::cout << "\nRating: " << row[6];

           mysql_free_result(res);
           return true;
        }
        mysql_free_result(res);
    }
    else
    {
        std::cout << "BOOK NOT FOUND :(\n";
        return false;
    }
    return false;
}

void searchBooks(MYSQL *conn)
{
    char temp;
    std::string title;
    std::string ISBN;
    std::cout << "Search by Title or ISBN [T/I]: ";
    std::cin >> temp;
    while(temp != 'T' && temp != 'I')
    {
        std::cout << "Search by Title or ISBN [T/I]: ";
        std::cin >> temp;
    }
    if(temp == 'T')
    {
        std::cout << "Enter Title: ";
        std::cin >> title;
        searchName(conn, title);
    }
    else
    {
        std::cout << "Enter ISBN: ";
        std::cin >> ISBN;
        searchISBN(conn, ISBN);
    }
}

void addReview(MYSQL *conn, std::string ISBN, std::string username)
{
    // Fetch the current rating and number of ratings for the book
    char query_fetch[1000];
    sprintf(query_fetch, "SELECT prev_rating, num_ratings FROM BOOK WHERE ISBN='%s'", ISBN.c_str());
    MYSQL_RES *res;
    MYSQL_ROW row;

    if(mysql_query(conn, query_fetch)) {
        std::cout << "Error querying book details.\n";
        return;
    }

    res = mysql_store_result(conn);
    if((row = mysql_fetch_row(res)) == NULL) {
        std::cout << "Book not found.\n";
        mysql_free_result(res);
        return;
    }

    double prev_rating = atof(row[0]);
    int num_ratings = atoi(row[1]);
    mysql_free_result(res);

    // Fetch existing rate by this user for the book
    int rate = 0;
    char query_user_rate[1000];
    sprintf(query_user_rate, "SELECT rate FROM CHECK_OUT WHERE check_out_ISBN='%s' AND check_out_id='%s'", ISBN.c_str(), username.c_str());

    if(mysql_query(conn, query_user_rate)) {
        std::cout << "Error querying user rate.\n";
        return;
    }

    res = mysql_store_result(conn);
    if((row = mysql_fetch_row(res))) {
        rate = atoi(row[0]);  // Use existing rate if available
        mysql_free_result(res);
    } else {
        // If no existing rate found, prompt user to enter a new rating
        mysql_free_result(res);
        std::cout << "No previous rating found by user. Enter your rating (0-5): ";
        std::cin >> rate;
    }

    // Update the book's rating and number of ratings
    char query_update[1000];
    sprintf(query_update, "UPDATE BOOK SET prev_rating = ((prev_rating * num_ratings + %d) / (num_ratings + 1)), num_ratings = num_ratings + 1 WHERE ISBN='%s'", rate, ISBN.c_str());

    if(mysql_query(conn, query_update)) {
        std::cout << "Error updating book rating.\n";
    } else {
        std::cout << "Rating updated successfully!\n";
    }
}

void viewBorrowHistory(MYSQL *conn, std::string username)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1000];

    // Construct the SQL query to find the previous books borrowed by the user
    sprintf(query, "SELECT prev_book_ISBN, title FROM USER_PREV_BOOKS JOIN BOOK ON USER_PREV_BOOKS.prev_book_ISBN = BOOK.ISBN WHERE users_id='%s'", username.c_str());

    // Execute the query
    if(mysql_query(conn, query))
    {
        std::cout << "ERROR QUERYING DATABASE\n";
        return;
    }

    // Store the result of the query
    res = mysql_store_result(conn);
    if(!res)
    {
        std::cout << "ERROR RETRIEVING QUERY RESULTS\n";
        return;
    }

    // Check if any rows are returned
    if(mysql_num_rows(res) == 0)
    {
        std::cout << "No borrowing history found for user ID: " << username << "\n";
        mysql_free_result(res);
        return;
    }

    // Output the titles and ISBNs of the previously borrowed books
    std::cout << "Borrowing History for User ID " << username << ":\n";
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        std::cout << "ISBN: " << row[0] << " - Title: " << row[1] << "\n";
    }

    // Clean up the result set
    mysql_free_result(res);
}

void manageAccount(MYSQL *conn, bool admin, std::string username)
{
    std::string targetUser;
    std::string newPassword;
    char query[1000];
    MYSQL_RES *res;
    MYSQL_ROW row;

    // If the user is an admin, they can choose which account to manage
    if (admin) {
        std::cout << "Enter employee_id or user_id to manage: ";
        std::cin >> targetUser;
    } else {
        // Non-admin users can only manage their own account
        targetUser = username;
    }

    // Determine if the target user is a librarian or a patron
    sprintf(query, "SELECT 'Librarian' as Role FROM LIBRARIAN WHERE e_id='%s' UNION SELECT 'Patron' as Role FROM PATRON WHERE user_id='%s'", targetUser.c_str(), targetUser.c_str());
    if (mysql_query(conn, query)) {
        std::cout << "Error checking user role: " << mysql_error(conn) << "\n";
        return;
    }

    res = mysql_store_result(conn);
    if (!res || mysql_num_rows(res) == 0) {
        std::cout << "User not found.\n";
        if (res) {
            mysql_free_result(res);
        }
        return;
    }

    row = mysql_fetch_row(res);
    std::string role = row[0]; // This should contain 'Librarian' or 'Patron'
    mysql_free_result(res);

    // Prompt for the new password
    std::cout << "Enter new password for " << (role == "Librarian" ? "librarian" : "patron") << " ID " << targetUser << ": ";
    std::cin >> newPassword;

    // Set the table and column names based on the role
    std::string table = role == "Librarian" ? "LIBRARIAN" : "PATRON";
    std::string idColumn = role == "Librarian" ? "employee_id" : "user_id";
    std::string passwordColumn = role == "Librarian" ? "e_pass" : "user_pass";

    // Prepare the query to update the password
    sprintf(query, "UPDATE %s SET %s='%s' WHERE %s='%s'", table.c_str(), passwordColumn.c_str(), newPassword.c_str(), idColumn.c_str(), targetUser.c_str());

    // Execute the query
    if (mysql_query(conn, query)) {
        std::cout << "ERROR UPDATING PASSWORD: " << mysql_error(conn) << "\n";
    } else {
        std::cout << "Password updated successfully for " << (role == "Librarian" ? "librarian" : "patron") << " ID " << targetUser << "\n";
    }
}

void checkout();

void checkIn(MYSQL *conn)
{
    std::string username, userid;
    std::cout << "What is the patron's name (e.x. John Doe): ";
    std::cin >> username;
    userid = userID(conn, username);

    std::string ISBN;
    std::cin.clear();
    std::cout << "Enter book's ISBN: ";
    std::cin >> ISBN;
    std::cin.clear();
    std::string updateCheckout = "UPDATE CHECK_OUT SET return_date = CURDATE() WHERE check_out_id = '" + userid + "' AND check_out_ISBN = '" + ISBN + "'";
    mysql_query(conn, updateCheckout.c_str());
    if(mysql_affected_rows(conn) == 0)
    {
        std::cout << "No book matching that ISBN has been found";
    }
    std::string updatePrevBooks = "INSERT INTO USER_PREV_BOOKS (user_id, prev_book_ISBN) VALUES ('" + userid + ", '" + ISBN + "')'";
    std::string updateAvailability = "UPDATE BOOK SET availability = availability + 1 WHERE ISBN = '" + ISBN + "'";
    mysql_query(conn, updateAvailability.c_str());

    std::string rate;
    std::cin.clear();
    std::cout << std::endl << "Enter a rating (1-5): ";
    std::cin >> rate;
    std::string updateRating = "UPDATE CHECK_OUT SET rate = " + rate + "WHERE check_out_id = '" + userid + "' AND check_out_ISBN = '" + ISBN + "'";
    mysql_query(conn, updateRating.c_str());

    std::cout << "Book has been checked in" << std::endl;
}

void addBooks(MYSQL *conn) {
    std::string ISBN, title, author, publish_date;
    int page_count, additional_copies;
    int prev_rating = 0;  // Assuming new books start with no ratings
    int num_ratings = 0;  // Initializing num_ratings to 0 for new books

    // Collect book details from user
    std::cout << "Enter ISBN: ";
    std::getline(std::cin, ISBN);
    std::cout << "Enter Title: ";
    std::getline(std::cin, title);
    std::cout << "Enter Author: ";
    std::getline(std::cin, author);
    std::cout << "Enter Publish Date (YYYY-MM-DD): ";
    std::getline(std::cin, publish_date);
    std::cout << "Enter Page Count: ";
    std::cin >> page_count;
    std::cin.ignore();
    std::cout << "Enter number of copies to add: ";
    std::cin >> additional_copies;
    std::cin.ignore();

    // Check if the book already exists in the database
    char check_query[1000];
    sprintf(check_query, "SELECT availability FROM BOOK WHERE ISBN='%s'", ISBN.c_str());
    if (mysql_query(conn, check_query)) {
        std::cout << "ERROR CHECKING BOOK EXISTENCE: " << mysql_error(conn) << "\n";
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (mysql_num_rows(res) > 0) {
        MYSQL_ROW row = mysql_fetch_row(res);
        int current_availability = atoi(row[0]);
        mysql_free_result(res);

        // Book exists, update the availability
        int new_availability = current_availability + additional_copies;
        char update_query[1000];
        sprintf(update_query, "UPDATE BOOK SET availability = %d WHERE ISBN='%s'", new_availability, ISBN.c_str());
        if (mysql_query(conn, update_query)) {
            std::cout << "ERROR UPDATING BOOK AVAILABILITY: " << mysql_error(conn) << "\n";
        } else {
            std::cout << "Book availability updated successfully. Total available now: " << new_availability << "\n";
        }
        return;
    } else {
        // If the book does not exist, insert the new book into the database
        char insert_query[1000];
        sprintf(insert_query, "INSERT INTO BOOK (ISBN, title, author, publish_date, page_count, availability, prev_rating, num_ratings) VALUES ('%s', '%s', '%s', '%s', %d, %d, %d, %d)",
            ISBN.c_str(), title.c_str(), author.c_str(), publish_date.c_str(), page_count, additional_copies, prev_rating, num_ratings);

        // Execute the query
        if (mysql_query(conn, insert_query)) {
            std::cout << "ERROR ADDING BOOK: " << mysql_error(conn) << "\n";
        } else {
            std::cout << "New book added successfully with " << additional_copies << " copies available.\n";
        }
    }
    mysql_free_result(res);

}

void editBooks(MYSQL *conn) {
    std::string ISBN, title, author, publish_date;
    int page_count = -1;
    int availability = -1;
    std::string query = "UPDATE BOOK SET ";

    // Ask for ISBN to identify the book to edit
    std::cout << "Enter ISBN of the book to edit: ";
    std::getline(std::cin, ISBN);

    // Check if the book exists
    char check_query[1000];
    sprintf(check_query, "SELECT * FROM BOOK WHERE ISBN='%s'", ISBN.c_str());
    if (mysql_query(conn, check_query)) {
        std::cout << "ERROR CHECKING BOOK EXISTENCE: " << mysql_error(conn) << "\n";
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (mysql_num_rows(res) == 0) {
        std::cout << "No book found with ISBN " << ISBN << ".\n";
        mysql_free_result(res);
        return;
    }
    mysql_free_result(res);  // Free result as soon as it is no longer needed

    // Book exists, collect new details from user
    std::cout << "Enter new Title (or press Enter to skip): ";
    std::getline(std::cin, title);
    std::cout << "Enter new Author (or press Enter to skip): ";
    std::getline(std::cin, author);
    std::cout << "Enter new Publish Date (YYYY-MM-DD or press Enter to skip): ";
    std::getline(std::cin, publish_date);
    std::cout << "Enter new Page Count (or -1 to skip): ";
    std::cin >> page_count;
    std::cin.ignore();
    std::cout << "Enter new Availability (number of copies or -1 to skip): ";
    std::cin >> availability;
    std::cin.ignore();

    bool first = true;

    if (!title.empty()) {
        query += "title = '" + title + "'";
        first = false;
    }

    if (!author.empty()) {
        if (!first)
            query += ", ";
        query += "author = '" + author + "'";
        first = false;
    }

    if (!publish_date.empty()) {
        if (!first)
            query += ", ";
        query += "publish_date = '" + publish_date + "'";
        first = false;
    }

    if (page_count != -1) {
        if (!first)
            query += ", ";
        query += "page_count = " + std::to_string(page_count);
        first = false;
    }

    if (availability != -1) {
        if (!first)
            query += ", ";
        query += "availability = " + std::to_string(availability);
        first = false;
    }

    query += " WHERE ISBN = '" + ISBN + "'";

    // Execute the update query
    if (mysql_query(conn, query.c_str())) {
        std::cout << "ERROR UPDATING BOOK: " << mysql_error(conn) << "\n";
    } else {
        std::cout << "Book updated successfully.\n";
    }
}

void removeBooks(MYSQL *conn) {
    std::string ISBN;
    int remove_count, current_availability;

    // Ask for ISBN to identify the book to remove copies from
    std::cout << "Enter ISBN of the book to remove copies from: ";
    std::getline(std::cin, ISBN);

    // Check current availability
    char query[1000];
    sprintf(query, "SELECT availability FROM BOOK WHERE ISBN='%s'", ISBN.c_str());
    if (mysql_query(conn, query)) {
        std::cout << "Error checking book availability: " << mysql_error(conn) << "\n";
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res || mysql_num_rows(res) == 0) {
        std::cout << "No book found with ISBN " << ISBN << ".\n";
        if (res) {
            mysql_free_result(res);
        }
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    current_availability = atoi(row[0]);
    mysql_free_result(res);

    std::cout << "Current availability of the book: " << current_availability << "\n";
    std::cout << "How many copies would you like to remove? ";
    std::cin >> remove_count;
    std::cin.ignore();

    if (remove_count > current_availability) {
        std::cout << "Cannot remove more copies than are available.\n";
        return;
    }

    // Update availability
    int new_availability = current_availability - remove_count;
    sprintf(query, "UPDATE BOOK SET availability = %d WHERE ISBN='%s'", new_availability, ISBN.c_str());
    if (mysql_query(conn, query)) {
        std::cout << "Error updating book availability: " << mysql_error(conn) << "\n";
    } else {
        std::cout << "Updated the book successfully. New availability: " << new_availability << ".\n";
    }
}

void addNewUser(MYSQL *conn)
{
    char type;
    int newID;
    std::cout << "Account type (Patron(P)/Librarian(L)): ";
    std::cin >> type;
    while(type != 'P' && type != 'L')
    {
        std::cout << "Invalid type! Account type (Patron(P)/Librarian(L)) :";
        std::cin >> type;
    }

    std::string username, address, birthday, password, query;
    std::cout << "Enter username (e.x. John Doe): ";
    std::cin.ignore();
    std::getline(std::cin, username);
    std::cout << "Enter address: ";
    std::cin.ignore();
    std::getline(std::cin, address);
    std::cout << "Enter birthday (YYYY-MM-DD): ";
    std::cin >> birthday;
    std::cout << "Enter password: ";
    std::cin >> password;

    if(type == 'P')
    {
        newID = getMaxID(conn, "PATRON", "user_id") + 1;
        query = "INSERT INTO PATRON (user_id, user_name, user_address, user_birthday, user_pass) VALUES (" + std::to_string(newID) + ", '" + username + "', '" + address + "', '" + birthday + "', '" + password + "')";
    }
    else
    {
        int branchNo;
        newID = getMaxID(conn, "LIBRARIAN", "e_id") + 1;
        std::cout << "Enter branch number: ";
        std::cin >> branchNo;
        query = "INSERT INTO LIBRARIAN (e_id, e_name, e_branch_no, e_pass) VALUES (" + std::to_string(newID) + ", '" + username + "', " + std::to_string(branchNo) + ", '" + password + "')";
        std::cout << query;
    }

    if(mysql_query(conn, query.c_str()))
    {
        std::cout << "Error creating new account";
        return;
    }

    std::cout << "New account successfully created" << std::endl;
}
