#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "book.h"  // Include the header file for the Book class

TEST_CASE("Load books from CSV file", "[loadBooksFromLibrary]") {
    // Create a temporary file with sample book data
    std::ofstream tempFile("temp_books.csv");
    tempFile << "1,Book1,300,Author1,LastName1,Fiction\n"
             << "2,Book2,250,Author2,LastName2,Non-Fiction\n"
             << "3,Book3,200,Author3,LastName3,Science\n";
    tempFile.close();

    SECTION("Valid file path") {
        // Load books from the temporary file
        std::vector<Book> books = Book::loadBooksFromLibrary("temp_books.csv");

        // Check the size of the loaded books vector
        REQUIRE(books.size() == 3);

        // Check specific details of the loaded books
        REQUIRE(books[0].getBookID() == 1);
        REQUIRE(books[0].getBookName() == "Book1");
        REQUIRE(books[0].getPageCount() == 300);
        REQUIRE(books[0].getAuthorFirstName() == "Author1");
        REQUIRE(books[0].getAuthorLastName() == "LastName1");
        REQUIRE(books[0].getBookType() == "Fiction");

        // Add more similar checks for the other two books

        // Remove the temporary file
        std::remove("temp_books.csv");
    }

    SECTION("Invalid file path") {
        // Load books from an invalid file path
        std::vector<Book> books = Book::loadBooksFromLibrary("nonexistent_file.csv");

        // Check that the loaded books vector is empty
        REQUIRE(books.empty());
    }
}
