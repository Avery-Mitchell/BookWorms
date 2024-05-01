#										CREATING THE DATABASE
#DROP DATABASE BOOKWORMS;

#CREATE DATABASE BOOKWORMS;

USE BOOKWORMS; 

/*
CREATE TABLE LIBRARY (
    l_code INT NOT NULL,
    l_name VARCHAR(60)	NOT NULL,
    address VARCHAR(60) NOT NULL,
    PRIMARY KEY (l_code)
);

#assumptions incluse each branch has a unique branch number even if branches are associated with different libraries

CREATE TABLE BRANCH (
    lib_code INT NOT NULL,
    branch_no INT	NOT NULL,
    b_name VARCHAR(60),
    b_address VARCHAR(60),
    PRIMARY KEY (branch_no),
    FOREIGN KEY (lib_code) REFERENCES LIBRARY(l_code)
);

CREATE TABLE LIBRARIAN(
	e_id INT	NOT NULL,
    e_name VARCHAR(20),
    e_branch_no INT,
    e_pass VARCHAR(30) NOT NULL,
    PRIMARY KEY (e_id),
    FOREIGN KEY (e_branch_no) REFERENCES BRANCH(branch_no)
    );

CREATE TABLE PATRON (
    user_id INT NOT NULL,
    user_name VARCHAR(20),
    user_address VARCHAR(60),
    user_birthday DATE,
    user_pass VARCHAR(30) NOT NULL,
    PRIMARY KEY (user_id)
);

CREATE TABLE BOOK (
	ISBN BIGINT NOT NULL,
    title VARCHAR(50) NOT NULL,
    author VARCHAR(20),
    publish_date DATE,
    page_count INT,
    availability BOOLEAN NOT NULL,
    prev_rating FLOAT(1),
    num_ratings INT
);

ALTER TABLE BOOK ADD INDEX idx_ISBN (ISBN);


CREATE TABLE USER_PREV_BOOKS (
	users_id INT NOT NULL,
    prev_book_ISBN BIGINT NOT NULL,
    FOREIGN KEY (users_id) REFERENCES PATRON(user_id),
    FOREIGN KEY (prev_book_ISBN) REFERENCES BOOK(ISBN)
);

CREATE TABLE BOOK_GENRES (
	book_ISBN BIGINT NOT NULL,
    genre VARCHAR(20) NOT NULL,
    FOREIGN KEY (book_ISBN) REFERENCES BOOK(ISBN)
);

CREATE TABLE CHECK_OUT (
	check_out_id INT NOT NULL,
    check_out_ISBN BIGINT NOT NULL,
    rate INT,
    checkout_date DATE,
    return_date DATE,
    FOREIGN KEY (check_out_id) REFERENCES PATRON(user_id),
    FOREIGN KEY (check_out_ISBN) REFERENCES BOOK(ISBN)
);

CREATE TABLE BOOK_BRANCH (
	book_branch_no INT NOT NULL,
    b_ISBN BIGINT NOT NULL,
    FOREIGN KEY (book_branch_no) REFERENCES BRANCH(branch_no),
    FOREIGN KEY (b_ISBN) REFERENCES BOOK(ISBN)
);


#										FILLING WITH DATA

INSERT INTO LIBRARY 
	Values (123, 'Phelps County Library', '165 N St, Rolla, MO'), (124, 'St. Louis County Library', '265 Main St, Chesterfield, MO'), (125, 'St Charles County Library', '174 Oak St, St.Charles, MO'), (126, 'Lincoln County Library', '199 Winding Rd, Troy, MO'), (127, 'Franklin County Library', '634 Pertersberg Ave, Union, MO');

INSERT INTO BRANCH
	Values (123, 01, 'Book Haven', '222 Reading Rd, Rolla, MO'), (123, 02, 'Page Turners', '482 Library Ln, St. James, MO'), (123, 03, 'Literary Lounge', '612 Page Turn Path, Newburg, MO'), (124, 04, 'Story Central', '385 Story St, Wildwood, MO'), (124, 05, 'Paper Paradise', '819 Ever After Ave, Florissant, MO');

INSERT INTO LIBRARIAN
	Values (189438, 'Brian O\'Hare', 03, '1<3b00k$'), (178923, 'Sherry Smith', 03, 'R3AD3R'), (817203, 'Rahul Muddu', 02, 'library4life'), (194852, 'Austin Zheng', 01, 'booksRc00l'), (628495, 'Amanda Depke', 02, 'b00kn00k');

INSERT INTO PATRON
	Values (840829, 'Josiah Nicholson', '456 Novel Ave, Rolla, MO', '1999-10-05', 'j0s!ah'), (549275, 'David Blevins', '189 Storybook St, St. James, MO', '2001-07-20', 'blevyreads'), (290378, 'Haroon Trevino', ' 920 Literary Ln, Wildwood, MO', '1983-12-11', 'password123'), (316372, 'Keith Stephenson', '829 Dewey Decimal Dr, Florissant, MO', '2005-03-30', 'K3!thS'),(906849, 'Nora Graves', '918 Bookworm Boulevard, Troy, MO', '1976-07-26', 'gr@vy');
    
INSERT INTO BOOK
	Values (9780545010221, 'Harry Potter and the Deathly Hallows', 'J.K. Rowling', '2009-07-31', 607, 0, 4.5, 1254), (9780804189354, 'The Martian', 'Andy Weir', '2011-05-04', 400, 1, 4.3, 567), (9780064400558, 'Charlotte\'s Web', 'E.B. White', '1952-10-15', 184, 0, 3.7, 459), (9780486828060, 'Little Women', 'Louisa May Alcott', '1868-9-30', 480, 1, 3.2, 692), (9780060598242, 'The Chronicles of Narnia', 'C.S. Lewis', '1953-09-23', 784, 1, 3.5, 291);
    
INSERT INTO USER_PREV_BOOKS
	Values (840829, 9780545010221), (840829, 9780804189354), (840829, 9780064400558), (549275, 9780545010221), (290378, 9780545010221);
    
INSERT INTO BOOK_GENRES
	Values (9780545010221, 'Adventure'), (9780545010221, 'Fantasy'), (9780804189354, 'Sci-Fi'), (9780064400558, 'Young Adult'), (9780486828060, 'Coming-of-age'), (9780060598242, 'Fantasy'), (9780060598242, 'Action');
    
INSERT INTO CHECK_OUT
	Values (840829, 9780545010221, 4, '2022-05-17', '2022-06-17'), (840829, 9780064400558, 3, '2024-01-23', '2024-02-24'), (549275, 9780060598242, NULL, '2024-05-01', NULL), (290378, 9780545010221, 5, '2020-12-04', '2021-01-28'), (549275, 9780486828060, 4, '2024-02-14', '2024-03-14');
    
INSERT INTO BOOK_BRANCH
	Values (01, 9780545010221), (01, 9780804189354), (04, 9780064400558), (03, 9780060598242), (03, 9780486828060);
*/