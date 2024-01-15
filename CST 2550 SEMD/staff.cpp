// staff.cpp

#include "staff.h"

// Constructor to initialize staff member with provided information
staff::staff(const std::string& name, const std::string& addr, const std::string& email, const std::string& pwd)
    : fullName(name), address(addr), emailID(email), password(pwd) {}

// Login function to verify staff member's credentials
bool staff::login(const std::string& email, const std::string& pwd) const {
    return (email == emailID && pwd == password);
}

// Getter function to retrieve staff member's full name
std::string staff::getFullName() const {
    return fullName;
}

std::string staff::getAddress() const {
    return address;
}

std::string staff::getEmailID() const {
    return emailID;
}

std::string staff::getPassword() const
{
    return password;
}

// Getter function to retrieve staff member's staff ID
std::string staff::getStaffId() const
{
    return staffId;
}
