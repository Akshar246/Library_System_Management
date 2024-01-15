#include "book.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructors
Book::Book() : bookID(0), pageCount(0) {}

Book::Book(const int bookID, const std::string &bookName, int pageCount, const std::string &authorFirstName, const std::string &authorLastName, const std::string &bookType)
    : bookID(bookID), bookName(bookName), authorFirstName(authorFirstName), authorLastName(authorLastName), pageCount(pageCount), bookType(bookType) {}

// Getter methods
int Book::getBookID() const
{
    return bookID;
}

std::string Book::getBookName() const
{
    return bookName;
}

int Book::getPageCount() const
{
    return pageCount;
}

std::string Book::getAuthorFirstName() const
{
    return authorFirstName;
}

std::string Book::getAuthorLastName() const
{
    return authorLastName;
}

std::string Book::getBookType() const
{
    return bookType;
}

// Load books from CSV file
std::vector<Book> Book::loadBooksFromLibrary(const std::string &filePath)
{
    std::vector<Book> books;

    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::cerr << "Error opening file: " << filePath << "\n";
        return books;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(iss, token, ','))
        {
            tokens.push_back(token);
        }

        if (tokens.size() == 6)
        {
            try
            {
                int bookID = std::stoi(tokens[0]);
                int pageCount = std::stoi(tokens[2]);

                Book book(bookID, tokens[1], pageCount, tokens[3], tokens[4], tokens[5]);
                books.push_back(book);
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Invalid argument: " << e.what() << "\n";
            }
        }
    }

    inFile.close();
    return books;
}

// Display books by category
void Book::displayBooksByCategory(const std::vector<Book> &books, const std::string &category)
{
    bool found = false;

    for (const auto &book : books)
    {
        if (book.getBookType() == category)
        {
            if (!found)
            {
                std::cout << "Books in category '" << category << "':\n";
                found = true;
            }
            std::cout << "------------------------\n";
        }
    }

    if (!found)
    {
        std::cout << "No books found in category '" << category << "'.\n";
    }
}

std::vector<Book> Book::getBooksByCategory(const std::vector<Book> &books, const std::string &category)
{
    std::vector<Book> booksInCategory;

    for (const auto &book : books)
    {
        if (book.getBookType() == category)
        {
            booksInCategory.push_back(book);
        }
    }

    return booksInCategory;
}
