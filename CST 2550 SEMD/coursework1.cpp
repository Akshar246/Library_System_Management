#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "staff.h"
#include "member.h"
#include "book.h"

// Function for the Book categories
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

// Function to display all available book categories with numbers
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

    // Trim trailing whitespaces
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
    std::transform(result.begin(), result.end(), result.begin(), (int (*)(int))std::tolower);
    return result;
}

// Function to load staff members from the file
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
                name = line.substr(6);          // Remove "Name: "
                std::getline(inFile, address);  // Assume next line is address
                std::getline(inFile, email);    // Assume next line is email
                std::getline(inFile, password); // Assume next line is password

                // Create a staff object and add to the vector
                staff loadedStaff(name, address, email, password);
                loadedStaffMembers.push_back(loadedStaff);
            }
        }
        inFile.close();
    }
    return loadedStaffMembers;
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

// Function to get books by category
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

// Function to display books
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

// Function to trim leading and trailing whitespaces from a string
// Function to trim leading and trailing whitespaces from a string
static std::string trim(const std::string &s);

// Function to convert a string to lowercase
static std::string tolower(const std::string &s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), (int (*)(int))std::tolower);
    return result;
}

std::vector<std::string> getBooksByCategory(const std::vector<std::string> &allBooks, const std::string &category);

// Function to display books
void displayBooks(const std::vector<std::string> &books);

int main()
{
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
    // Initialize members vector for new members
    std::vector<Member> members;
    std::vector<std::string> bookCategories = getBookCategories();

    // Dummy data for demonstration purposes
    staff staff1("Akshar", "123", "a@gmail.com", "1234");
    staffMembers.push_back(staff1);

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

                    Member members; // Declare outside the switch statement with a default constructor

                    switch (std::stoi(choice))
                    {
                    case 1:
                        members = Member::loginOrRegister();
                        // Handle member login or registration logic
                        // ...
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
