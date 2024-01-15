
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "staff.h"

TEST_CASE("Staff Login Test", "[staff][login]") {
    // Create a staff member for testing
    staff testStaff("John Doe", "123 Main St", "john.doe@example.com", "password123");

    SECTION("Valid Login") {
        REQUIRE(testStaff.login("john.doe@example.com", "password123") == true);
    }

    SECTION("Invalid Email") {
        REQUIRE(testStaff.login("invalid@example.com", "password123") == false);
    }

    SECTION("Invalid Password") {
        REQUIRE(testStaff.login("john.doe@example.com", "wrongpassword") == false);
    }
}

TEST_CASE("Staff Getter Functions Test", "[staff][getters]") {
    // Create a staff member for testing
    staff testStaff("Jane Smith", "456 Oak St", "jane.smith@example.com", "securepassword");

    SECTION("Full Name Getter") {
        REQUIRE(testStaff.getFullName() == "Jane Smith");
    }

    SECTION("Address Getter") {
        REQUIRE(testStaff.getAddress() == "456 Oak St");
    }

    SECTION("Email ID Getter") {
        REQUIRE(testStaff.getEmailID() == "jane.smith@example.com");
    }

    SECTION("Password Getter") {
        // For testing purposes only; in real-world scenarios, you wouldn't expose the password
        REQUIRE(testStaff.getPassword() == "securepassword");
    }

    SECTION("Staff ID Getter") {
        // You might modify this section based on your specific implementation
        REQUIRE(testStaff.getStaffId() == ""); // Assuming staff ID is not set in this test
    }
}
