#CREATE DATABASE BOOKWORMS

USE BOOKWORMS; 

/*
CREATE TABLE LIBRARY (
    l_code INT NOT NULL,
    l_name VARCHAR(20)	NOT NULL,
    address VARCHAR(20) NOT NULL,
    PRIMARY KEY (l_code)
);

CREATE TABLE BRANCH (
    lib_code INT NOT NULL,
    branch_no INT	NOT NULL,
    b_name VARCHAR(20),
    b_address VARCHAR(20),
    PRIMARY KEY (branch_no),
    FOREIGN KEY (lib_code) REFERENCES LIBRARY(l_code)
);

CREATE TABLE LIBRARIAN(
	e_id INT	NOT NULL,
    e_name VARCHAR(20),
    e_branch_no INT,
    PRIMARY KEY (e_id),
    FOREIGN KEY (e_branch_no) REFERENCES BRANCH(branch_no)
    );

CREATE TABLE PATRON (
    user_id INT NOT NULL,
    user_name VARCHAR(20),
    user_address VARCHAR(20),
    user_birthday DATE,
    PRIMARY KEY (user_id)
);

CREATE TABLE BOOK (
	ISBN INT NOT NULL,
    title VARCHAR(50) NOT NULL,
    author VARCHAR(20),
    publish_date DATE,
    page_count INT,
    availability BOOLEAN NOT NULL,
    prev_rating INT,
    num_ratings INT
);

ALTER TABLE BOOK ADD INDEX idx_ISBN (ISBN);


CREATE TABLE USER_PREV_BOOKS (
	users_id INT NOT NULL,
    prev_book_ISBN INT NOT NULL,
    FOREIGN KEY (users_id) REFERENCES PATRON(user_id),
    FOREIGN KEY (prev_book_ISBN) REFERENCES BOOK(ISBN)
);

CREATE TABLE BOOK_GENRES (
	book_ISBN INT NOT NULL,
    genre VARCHAR(10) NOT NULL,
    FOREIGN KEY (book_ISBN) REFERENCES BOOK(ISBN)
);

CREATE TABLE CHECK_OUT (
	check_out_id INT NOT NULL,
    check_out_ISBN INT NOT NULL,
    rate INT,
    checkout_date DATE,
    return_date DATE,
    FOREIGN KEY (check_out_id) REFERENCES PATRON(user_id),
    FOREIGN KEY (check_out_ISBN) REFERENCES BOOK(ISBN)
);

CREATE TABLE BOOK_BRANCH (
	book_branch_no INT NOT NULL,
    branch_l_code INT NOT NULL,
    b_ISBN INT NOT NULL,
    FOREIGN KEY (book_branch_no) REFERENCES BRANCH(branch_no),
    FOREIGN KEY (branch_l_code) REFERENCES LIBRARY(l_code),
    FOREIGN KEY (b_ISBN) REFERENCES BOOK(ISBN)
);
*/
    
    
    
    
