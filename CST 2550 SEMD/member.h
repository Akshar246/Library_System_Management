// member.h

#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>

class Member {
private:
    std::string name;
    std::string address;
    std::string email;
    std::string password;

public:
    // Constructors
    Member();
    Member(const std::string& name, const std::string& address, const std::string& email, const std::string& password);

    // Getter methods
    std::string getFullName() const;
    std::string getAddress() const;
    std::string getEmailID() const;
    std::string getPassword() const;

    // Member functions
    bool login(const std::string& email, const std::string& pass) const;
    void saveMemberToTxt() const;
    void inputMemberData();  // Added this function

    // Static method for login and register
    static Member loginOrRegister();
};

#endif // MEMBER_H
