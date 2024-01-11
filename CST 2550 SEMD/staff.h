#ifndef STAFF_H 
#define STAFF_H 

#include <string>

class staff {
private:
    std::string fullName;
    std::string address;
    std::string emailID;
    std::string password;  // To keep things simple, storing the password in plain text for this example. In real-world scenarios, always hash and salt passwords.
    std::string staffId;

public:
    // Constructor for signup
    staff(const std::string& name, const std::string& addr, const std::string& email, const std::string& pwd);

    // Function for login
    bool login(const std::string& email, const std::string& pwd) const;

    // Getter functions (optional, but can be useful)
    std::string getFullName() const;
    std::string getAddress() const;
    std::string getEmailID() const;
    std::string getPassword() const;
    std::string getStaffId() const; 
};

#endif // STAFF_H
