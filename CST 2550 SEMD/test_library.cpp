#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "library.h"

TEST_CASE("Library functionality", "[Library]") {
    SECTION("Add and Check Borrowed Books") {
        // Create a Library instance
        Library library;

        // Create some Book instances for testing
        Book book1(1, "Book1", 200, "Author1", "LastName1", "Fiction");
        Book book2(2, "Book2", 250, "Author2", "LastName2", "Non-Fiction");
        Book book3(3, "Book3", 300, "Author3", "LastName3", "Science");

        // Add books to the library as borrowed
        library.addBorrowedBook(book1);
        library.addBorrowedBook(book2);

        // Check if the added books are marked as borrowed
        REQUIRE(library.isBookBorrowed(book1) == true);
        REQUIRE(library.isBookBorrowed(book2) == true);
        REQUIRE(library.isBookBorrowed(book3) == false);
    }
}
