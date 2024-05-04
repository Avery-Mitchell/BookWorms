#include <iostream>
#include <cstring>
#include "database.h"

bool login(MYSQL *conn, bool& admin, std::string username, std::string password)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query1[1000];
    char query2[1000];

    sprintf(query1, "SELECT * FROM LIBRARIAN WHERE e_name='%s' AND e_pass='%s'", username.c_str(), password.c_str());
    sprintf(query2, "SELECT * FROM PATRON WHERE user_name='%s' AND user_pass='%s'", username.c_str(), password.c_str());

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
    sprintf(query, "SELECT 'Librarian' as Role FROM LIBRARIAN WHERE employee_id='%s' UNION SELECT 'Patron' as Role FROM PATRON WHERE user_id='%s'", targetUser.c_str(), targetUser.c_str());
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
