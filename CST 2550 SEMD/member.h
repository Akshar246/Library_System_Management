// member.h

#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>
#include <vector>
#include "book.h"

class Member
{
private:
    std::string name;
    std::string address;
    std::string email;
    std::string password;
    bool isLoggedIn;

public:
    Member();

    // Parameterized constructor
    Member(const std::string &name, const std::string &address, const std::string &email, const std::string &password);

    // Getter methods
    std::string getFullName() const;
    std::string getAddress() const;
    std::string getEmailID() const;
    std::string getPassword() const;
    bool getIsLoggedIn() const;

    // Member login
    bool login(const std::string &email, const std::string &pass);

    // Display borrowed books for the current member
    void displayBorrowedBooks() const;

    // Save member information to a text file
    void saveMemberToTxt() const;

    // Input member data during registration
    void inputMemberData();

    // Static function to handle member login or registration
    static Member loginOrRegister();

    // Static function to check if a member is logged in
    static bool isMemberLoggedIn(const Member &member);

    static std::vector<Member> loadMembersFromTxt();

    
};

#endif // MEMBER_H
