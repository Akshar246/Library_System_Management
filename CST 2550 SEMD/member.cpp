
#include "member.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Global vector to store member data
std::vector<Member> members;

// Default constructor
Member::Member() : isLoggedIn(false)
{
}

// Parameterized constructor
Member::Member(const std::string &name, const std::string &address, const std::string &email, const std::string &password)
    : name(name), address(address), email(email), password(password), isLoggedIn(false)
{
}

// Getter methods
std::string Member::getFullName() const
{
    return name;
}

std::string Member::getAddress() const
{
    return address;
}

std::string Member::getEmailID() const
{
    return email;
}

std::string Member::getPassword() const
{
    return password;
}

bool Member::getIsLoggedIn() const
{
    return isLoggedIn;
}

// Member login function
bool Member::login(const std::string &email, const std::string &pass)
{
    // Loop through existing members to find a match
    for (auto &member : members)
    {
        if (member.getEmailID() == email && member.getPassword() == pass)
        {
            // If a match is found, mark the member as logged in and save to file
            member.isLoggedIn = true;
            member.saveMemberToTxt();
            return true;
        }
    }
    return false; // Return false if no match is found
}

// Display borrowed books for the current member
void Member::displayBorrowedBooks() const
{
    std::ifstream inFile("borrowed_books.txt");
    if (!inFile.is_open())
    {
        std::cerr << "Error opening file: borrowed_books.txt\n";
        return;
    }

    std::string line;
    bool isCurrentMember = false;

    while (std::getline(inFile, line))
    {
        // Check if the line contains the current member's name
        if (line.find("Member Name: " + name) != std::string::npos)
        {
            isCurrentMember = true;
        }

        if (isCurrentMember)
        {
            std::cout << line << "\n";
        }

        // Check for the end of the current member's borrowed books section
        if (line.find("--------------------------") != std::string::npos)
        {
            isCurrentMember = false;
        }
    }

    inFile.close();
}


// Save member information to a text file
void Member::saveMemberToTxt() const
{
    std::ofstream outFile("member_Data.txt", std::ios::app);
    if (outFile.is_open())
    {
        // Write member information to the file
        outFile << "Name: " << name << "\n";
        outFile << "Address: " << address << "\n";
        outFile << "Email: " << email << "\n";
        outFile << "Password: " << password << "\n";
        outFile << "Login Status: " << (isLoggedIn ? "Logged In" : "Not Logged In") << "\n";
        outFile << "----------------------"
                << "\n";
        outFile.close();
        std::cout << "\nMember data saved in the database\n";
    }
    else
    {
        std::cout << "\nUnable to open file for writing.\n";
    }
}

// Input member data during registration
void Member::inputMemberData()
{
    std::cout << "\nEnter your full name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter your address: ";
    std::getline(std::cin, address);
    std::cout << "Enter your email: ";
    std::cin >> email;
    std::cout << "Enter password: ";
    std::cin >> password;
}

// Static function to handle member login or registration
Member Member::loginOrRegister()
{
    std::cout << "\nDo you have an account? (yes/no): ";
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
        for (auto &member : members)
        {
            if (member.login(email, password))
            {
                loggedIn = true;
                member.isLoggedIn = true;
                member.saveMemberToTxt();
                std::cout << "\nSuccessfully logged in.";
                std::cout << "\nNow you can borrow the books.\n Please enter to continue";
                std::cin.ignore();
                std::cin.get();
                break;
            }
        }

        if (!loggedIn)
        {
            std::cout << "Invalid email or password. Registering as a new member.\n";
            Member newMember;
            newMember.inputMemberData();
            members.push_back(newMember);
            newMember.saveMemberToTxt();
        }
    }
    else if (choice == "no")
    {
        Member newMember;
        newMember.inputMemberData();
        members.push_back(newMember);
        newMember.saveMemberToTxt();
    }
    else
    {
        std::cout << "\nInvalid choice. Please enter 'yes' or 'no'.\n";
    }

    return Member("", "", "", ""); // Return a default-constructed member
}
