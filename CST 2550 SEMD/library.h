
#pragma once
#include <set>
#include "book.h"

// Declaration of the Library class
class Library {
public:
    // Function to add a borrowed book to the library
    void addBorrowedBook(const Book& book);

    bool isBookBorrowed(const Book& book) const;

private:
    // Set to store the borrowed books in the library
    std::set<Book> borrowedBooks;
};
