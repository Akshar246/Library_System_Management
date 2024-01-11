#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>
#include <cctype>
#include <string>
#include "staff.h" // Assuming you have defined the staff class in this header file
#include "member.h"
#include "book.h"

// Function for the Book categories
std::vector<std::string> getBookCategories() {
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
        "Art"
    };
}


// Function to display all available book categories with numbers
void displayCategories(const std::vector<std::string>& categories) {
    std::cout << "Select a category by entering the corresponding number:\n\n";
    int index = 1;
    for (const auto& category : categories) {
        std::cout << index << ". " << category << "\n";
        ++index;
    }
}


// Function to trim leading and trailing whitespaces from a string
static inline std::string trim(const std::string &s) {
    std::string result = s;
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), result.end());

    return result;
}


// Function to get books by category
std::vector<Book> getBooksByCategory(const std::vector<Book> &books, const std::string &category) {
    std::vector<Book> booksInCategory;
    
    for (const auto &book : books) {
        if (trim(book.getBookType()) == trim(category)) {
            booksInCategory.push_back(book);
        }
    }

    return booksInCategory;
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

// Function to load books from txt file 
std::vector<Book> loadBooksFromLibrary(const std::string& filePath) {
    std::vector<Book> books;

    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << "\n";
        return books;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 6) {
            Book book(std::stoi(tokens[0]), tokens[1], std::stoi(tokens[2]), tokens[3], tokens[4], tokens[5]);
            books.push_back(book);
        }
    }

    inFile.close();
    return books;
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
    std::cout << "\nEnter your choice (1-4): ";
}

// Registration for the new member
void getMemberID(std::vector<Member> &members)
{
    std::string name, address, email, password;

    std::cout << "Enter full name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter address: ";
    std::getline(std::cin, address);
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Enter password: ";
    std::cin >> password;

    Member newMember(name, address, email, password);
    members.push_back(newMember);
}

int main()
{

    std::vector<staff> staffMembers = loadStaffFromTxt(); // Initialize staff members from file
    std::vector<Member> members;
    std::vector<Book> allBooks = Book::loadBooksFromLibrary("library_books.csv");
    std::vector<std::string> allCategories = getBookCategories();


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

                    switch (std::stoi(choice))
                    {
                    case 1: {
                            Member member = Member::loginOrRegister();
                        break;
                    }
                    case 2:
{
    std::cout << "Do you want to borrow a book (yes/no): ";
    std::cin >> choice;

    if (choice == "yes")
    {
        std::cout << "<------------------------BOOK CATEGORIES------------------>\n\n";
        displayCategories(allCategories);

        int categoryChoice;
        std::cout << "Enter the number of the category you want to explore: ";
        std::cin >> categoryChoice;

        if (categoryChoice >= 1 && categoryChoice <= allCategories.size())
        {
            std::string selectedCategory = allCategories[categoryChoice - 1];
            std::vector<Book> booksInCategory = Book::getBooksByCategory(allBooks, selectedCategory);

            if (!booksInCategory.empty())
            {
                Book::displayBooksByCategory(booksInCategory, selectedCategory);
            }
            else
            {
                std::cout << "No books found in category '" << selectedCategory << "'.\n";
            }
        }
        else
        {
            std::cout << "Invalid category selection.\n";
        }
    }
    break;
}

                    case 3:
                            std::cout << "Exiting the process. GoodBye!\n";
                            return 0;
                        break;

                    }
                } while (choice != "3");
            }
            else
            {
                std::cout << "Invalid email or password." << std::endl;
            }
        }
        else if (choice == "no")
        {
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
                std::cout << "\n\n\tNow you can 'login' as a Staff member\n\n";
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
