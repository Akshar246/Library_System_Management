
#include "library.h"

// Function to add a borrowed book to the library
void Library::addBorrowedBook(const Book& book) {
    borrowedBooks.insert(book);
}

// Function to check if a book is borrowed from the library
bool Library::isBookBorrowed(const Book& book) const {
    return borrowedBooks.find(book) != borrowedBooks.end();
}
