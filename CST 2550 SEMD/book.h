#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <set>

class Book {
private:
    int bookID;
    std::string bookName;
    std::string authorFirstName;
    std::string authorLastName;
    int pageCount;
    std::string bookType;

public:
    // Constructors
    Book();
    Book(const int bookID, const std::string& bookName, int pageCount,
         const std::string& authorFirstName, const std::string& authorLastName,
         const std::string& bookType);

    // Getter methods
    int getBookID() const;
    std::string getBookName() const;
    int getPageCount() const;
    std::string getAuthorFirstName() const;
    std::string getAuthorLastName() const;
    std::string getBookType() const;

    // Display book information
    void displayBookInfo() const;

    // Load books from CSV file
    static std::vector<Book> loadBooksFromLibrary(const std::string& filePath);

    // Display books by category
    static void displayBooksByCategory(const std::vector<Book>& books, const std::string& category);
    
static std::vector<Book> getBooksByCategory(const std::vector<Book>& books, const std::string& category);
};

#endif // BOOK_H

