// member.cpp

#include "member.h"
#include <iostream>
#include <fstream>

// Define a vector to store Member objects
std::vector<Member> members;

// Default constructor
Member::Member() {}

// Parameterized constructor
Member::Member(const std::string& name, const std::string& address, const std::string& email, const std::string& password)
    : name(name), address(address), email(email), password(password) {}

// Getter methods
std::string Member::getFullName() const {
    return name;
}

std::string Member::getAddress() const {
    return address;
}

std::string Member::getEmailID() const {
    return email;
}

std::string Member::getPassword() const {
    return password;
}

// Member login function
bool Member::login(const std::string& email, const std::string& pass) const {
    return (this->email == email && this->password == pass);
}

// Save Member data to a text file
void Member::saveMemberToTxt() const {
    std::ofstream outFile("member_Data.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << "Name: " << name << "\n";
        outFile << "Address: " << address << "\n";
        outFile << "Email: " << email << "\n";
        outFile << "Password: " << password << "\n";
        outFile << "----------------------" << "\n";
        outFile.close();
        std::cout << "\nMember data saved in the database\n";
    } else {
        std::cout << "\nUnable to open file for writing.\n";
    }
}

// Input Member data interactively
void Member::inputMemberData() {
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

// Static method for Member login or registration
Member Member::loginOrRegister() {
    std::cout << "\nDo you have an account? (yes/no): ";
    std::string choice;
    std::cin >> choice;

    if (choice == "yes") {
        std::string email, password;
        std::cout << "Enter email: ";
        std::cin >> email;
        std::cout << "Enter password: ";
        std::cin >> password;

        // Check if the entered credentials match any existing Member
        bool loggedIn = false;
        for (const auto& member : members) {
            if (member.login(email, password)) {
                loggedIn = true;
                break;
            }
        }

        // Display login status or prompt for registration
        if (loggedIn) {
            std::cout << "\nSuccessfully logged in.";
            std::cout << "\nNow you can borrow the books.\n Please enter to continue";
            std::cin.ignore();
            std::cin.get();
        } else {
            std::cout << "Invalid email or password. Registering as a new member.\n";
            Member newMember;
            newMember.inputMemberData();
            members.push_back(newMember);
            newMember.saveMemberToTxt();
        }
    } else if (choice == "no") {
        // Register a new Member
        Member newMember;
        newMember.inputMemberData();
        members.push_back(newMember);
        newMember.saveMemberToTxt();
    } else {
        std::cout << "\nInvalid choice. Please enter 'yes' or 'no'.\n";
    }

    // Return a default-constructed Member if neither 'yes' nor 'no'
    return Member("", "", "", ""); // Provide default values or modify as needed
}
