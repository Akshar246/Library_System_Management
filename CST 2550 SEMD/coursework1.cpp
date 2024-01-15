#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "staff.h"
#include "member.h"
#include "book.h"
#include "library.h"
#include <chrono>
#include <ctime>

// Function to get book categories
std::vector<std::string> getBookCategories()
{
    return {
        "Science fiction",
        "Satire",
        "Drama",
        "Action and Adventure",
        "Romance",
        "Mystery",
        "Horror",
        "Health",
        "Guide",
        "Diaries",
        "Comics",
        "Journals",
        "Biographies",
        "Fantasy",
        "History",
        "Science",
        "Art\n"};
}

// Function to display book categories with numbers
void displayCategories(const std::vector<std::string> &categories)
{
    int index = 1;
    for (const auto &category : categories)
    {
        std::cout << index << ". " << category << "\n";
        ++index;
    }
}

// Function to trim leading and trailing whitespaces from a string
static std::string trim(const std::string &s)
{
    std::string result = s;
    // Trim leading whitespaces
    result.erase(result.begin(), std::find_if(result.begin(), result.end(),
                                              [](unsigned char ch)
                                              { return !std::isspace(ch); }));

    result.erase(std::find_if(result.rbegin(), result.rend(),
                              [](unsigned char ch)
                              { return !std::isspace(ch); })
                     .base(),
                 result.end());
    return result;
}

// Function to convert a string to lowercase
static std::string toLower(const std::string &s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
                   { return std::tolower(c); });
    return result;
}

// Function to load members from a text file
std::vector<Member> loadMembersFromTxt()
{
    std::vector<Member> loadedMembers;
    std::ifstream inFile("member_Data.txt");
    if (inFile.is_open())
    {
        std::string line;
        while (std::getline(inFile, line))
        {
            std::string name, email, password;
            if (line.find("Name:") != std::string::npos)
            {
                name = line.substr(6);
                std::getline(inFile, email);
                std::getline(inFile, password);
            }
        }
        inFile.close();
    }
    return loadedMembers;
}

// Function to load staff members from a text file
std::vector<staff> loadStaffFromTxt()
{
    std::vector<staff> loadedStaffMembers;
    std::ifstream inFile("staff_data.txt");
    if (inFile.is_open())
    {
        std::string line;
        while (std::getline(inFile, line))
        {
            std::string name, address, email, password;
            if (line.find("Name:") != std::string::npos)
            {
                name = line.substr(6);
                std::getline(inFile, address);
                std::getline(inFile, email);
                std::getline(inFile, password);
                staff loadedStaff(name, address, email, password);
                loadedStaffMembers.push_back(loadedStaff);
            }
        }
        inFile.close();
    }
    return loadedStaffMembers;
}

// Function to get books by a specific category
std::vector<std::string> getBooksByCategory(const std::vector<std::string> &allBooks, const std::string &category)
{
    std::vector<std::string> booksInCategory;
    for (const auto &book : allBooks)
    {
        std::istringstream iss(book);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(iss, token, ','))
        {
            tokens.push_back(trim(token));
        }
        if (tokens.size() == 6)
        {
            std::string bookType = trim(tokens[5]);
            if (toLower(bookType) == toLower(category))
            {
                booksInCategory.push_back(book);
            }
        }
    }
    return booksInCategory;
}

// Function to display a list of books
void displayBooks(const std::vector<std::string> &books)
{
    if (books.empty())
    {
        std::cout << "No books found in the selected category.\n";
    }
    else
    {
        for (const auto &book : books)
        {
            std::cout << book << "\n";
        }
    }
}

// Function to check if a member is logged in
bool isMemberLoggedIn(const Member &member)
{
    return member.getIsLoggedIn();
}

// Main Menu for the user
void admin_Menu()
{
    std::cout << "\n\n\n\t\t\t******ADMINISTRATOR MENU******";
    std::cout << "\n1. Member Login";
    std::cout << "\n2. Book Issue";
    std::cout << "\n3. Return Book";
    std::cout << "\n4. Display All Books";
    std::cout << "\n5. Exit";
    std::cout << "\nEnter your choice (1-5): ";
}

// Main function
int main()
{
    Library Library;
    std::string dueDateString;
    std::ifstream inFile("library_books.csv");

    if (!inFile.is_open())
    {
        std::cerr << "Error opening file: library_books.csv\n";
        return 1;
    }
    std::vector<std::string> allBooks;
    std::string line;
    while (std::getline(inFile, line))
    {
        allBooks.push_back(line);
    }
    inFile.close();
    // Initialize staff members from file
    std::vector<staff> staffMembers = loadStaffFromTxt();
    std::vector<Member> members;
    std::vector<std::string> bookCategories = getBookCategories();
    // Dummy data for demonstration purposes
    staff staff1("Akshar", "123", "a@gmail.com", "1234");
    staffMembers.push_back(staff1);
    Member loggedInMember;

    // Main loop
    while (true)
    {
        std::cout << "Do you have staffID (yes/no): ";
        std::string choice;
        std::cin >> choice;
        if (choice == "yes")
        {
            std::string email, password;
            std::cout << "Enter email: ";
            std::cin >> email;
            std::cout << "Enter password: ";
            std::cin >> password;
            bool loggedIn = false;
            for (const auto &staff : staffMembers)
            {
                if (staff.login(email, password))
                {
                    loggedIn = true;
                    break;
                }
            }
            if (loggedIn)
            {
                std::cout << "Successfully logged in! Press enter to proceed." << std::endl;
                std::cin.ignore();
                std::cin.get();
                // Admin menu and options
                do
                {
                    admin_Menu();
                    std::cin >> choice;
                    Member loggedInMember;
                    switch (std::stoi(choice))
                    {
                    case 1:
                        loggedInMember = Member::loginOrRegister();
                        break;
                    case 2:
                    {
                        std::cout << "Do you want to borrow a book (yes/no): ";
                        std::cin >> choice;
                        if (choice == "yes")
                        {
                            std::cout << "<------------------------BOOK CATEGORIES------------------>\n\n";
                            displayCategories(bookCategories);
                            int categoryChoice;
                            std::cout << "Enter the number of the category you want to explore: \n\n";
                            std::cin >> categoryChoice;
                            if (categoryChoice >= 1 && categoryChoice <= bookCategories.size())
                            {
                                std::string selectedCategory = bookCategories[categoryChoice - 1];
                                std::vector<std::string> booksInCategory = getBooksByCategory(allBooks, selectedCategory);

                                // Display books
                                displayBooks(booksInCategory);

                                std::cout << "Enter the Book ID to borrow: ";
                                int bookID;
                                std::cin >> bookID;

                                // Logic to borrow the book
                                std::string selectedBook;
                                for (const auto &book : booksInCategory)
                                {
                                    std::istringstream iss(book);
                                    std::string token;
                                    std::vector<std::string> tokens;
                                    while (std::getline(iss, token, ','))
                                    {
                                        tokens.push_back(trim(token));
                                    }
                                    if (tokens.size() == 6 && std::stoi(tokens[0]) == bookID)
                                    {
                                        selectedBook = book;
                                        break;
                                    }
                                }

                                if (!selectedBook.empty())
                                {
                                    // Display borrowed book details
                                    std::cout << "\nCongratulations! You have successfully borrowed the following book:\n";
                                    std::cout << "Book details:\n";
                                    std::cout << "Borrowed book: " << selectedBook << "\n";

                                    // Calculate due date (three days from now)
                                    auto currentTime = std::chrono::system_clock::now();
                                    auto dueDate = currentTime + std::chrono::hours(24 * 3); // Three days
                                    std::time_t dueDate_time_t = std::chrono::system_clock::to_time_t(dueDate);
                                    std::cout << "Due date: " << std::ctime(&dueDate_time_t);

                                    // Notify about the penalty
                                    auto currentPenalty = std::chrono::system_clock::now();
                                    auto penaltyEndDate = currentPenalty + std::chrono::hours(24 * 3); // Three days (example, adjust as needed)
                                    std::time_t penaltyEndDate_time_t = std::chrono::system_clock::to_time_t(penaltyEndDate);
                                    std::cout << "\n*********************************************\n";
                                    std::cout << "  NOTICE: After the due date, a late fee of 1 pound per day will be charged.\n";
                                    std::cout << "  Don't let the fines pile up! Return the book by: " << std::ctime(&penaltyEndDate_time_t);
                                    std::cout << "*********************************************\n";
                                }
                                else
                                {
                                    std::cout << "Book not found.\n";
                                }
                            }
                            else
                            {
                                std::cout << "Invalid category choice.\n";
                            }
                        }
                        else if (choice == "no")
                        {
                            break;
                        }
                        break;
                    }
                    case 5:
                        std::cout << "Exiting the process. Goodbye!\n";
                        return 0;
                    default:
                        std::cout << "Invalid choice. Please enter a number between 1 and 5." << std::endl;
                        break;
                    }
                } while (choice != "5");
            }
        }
        else if (choice == "no")
        {
            // Registration for new staff member
            std::string name, address, email, password;
            std::cout << "Enter full name: ";
            std::cin.ignore(); // Ignore the newline character left in the buffer
            std::getline(std::cin, name);
            std::cout << "Enter address: ";
            std::getline(std::cin, address);
            std::cout << "Enter email: ";
            std::cin >> email;
            std::cout << "Enter password: ";
            std::cin >> password;
            staff newStaff(name, address, email, password);
            staffMembers.push_back(newStaff);
            // Store staff member's data in a txt file
            std::ofstream outFile("staff_data.txt", std::ios::app);
            if (outFile.is_open())
            {
                outFile << "Name: " << newStaff.getFullName() << "\n";
                outFile << "Address: " << newStaff.getAddress() << "\n";
                outFile << "Email: " << newStaff.getEmailID() << "\n";
                outFile << "Password: " << newStaff.getPassword() << "\n";
                outFile << "--------------------------\n";
                outFile.close();
                std::cout << "Registration successful!" << std::endl;
                std::cout << "\n\n\tNow you can 'login' as a staff member\n\n";
            }
            else
            {
                std::cout << "Unable to open file for writing." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid choice. Please enter 'yes' or 'no'." << std::endl;
        }
    }
    return 0;
}
