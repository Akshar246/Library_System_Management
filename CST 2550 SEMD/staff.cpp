#include "staff.h"

staff::staff(const std::string& name, const std::string& addr, const std::string& email, const std::string& pwd)
    : fullName(name), address(addr), emailID(email), password(pwd) {}

bool staff::login(const std::string& email, const std::string& pwd) const {
    return (email == emailID && pwd == password);
}

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

std::string staff::getStaffId() const
{
    return staffId;
}
