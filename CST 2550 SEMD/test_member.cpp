#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "member.h"

TEST_CASE("Member functionality", "[Member]") {
    // Load members from the text file
    std::vector<Member> members = Member::loadMembersFromTxt();

    SECTION("Login or Register - Existing Member") {
        // Create a member for testing
        Member testMember("Test Name", "", "test@email.com", "testpassword");
        members.push_back(testMember);

        // Redirect cin/cout to stringstream to capture user input/output
        std::stringstream input("yes\ntest@email.com\ntestpassword\n");
        std::stringstream output;

        std::streambuf* prev_cin = std::cin.rdbuf(input.rdbuf());
        std::streambuf* prev_cout = std::cout.rdbuf(output.rdbuf());

        // Perform login or registration
        Member resultMember = Member::loginOrRegister();

        // Reset cin/cout
        std::cin.rdbuf(prev_cin);
        std::cout.rdbuf(prev_cout);

        // Check if the member is logged in
        REQUIRE(resultMember.getIsLoggedIn());
    }

    SECTION("Login or Register - New Member") {
        // Redirect cin/cout to stringstream to capture user input/output
        std::stringstream input("no\nNew Test Name\nNew Test Address\nnewtest@email.com\nnewpassword\n");
        std::stringstream output;

        std::streambuf* prev_cin = std::cin.rdbuf(input.rdbuf());
        std::streambuf* prev_cout = std::cout.rdbuf(output.rdbuf());

        // Perform login or registration
        Member resultMember = Member::loginOrRegister();

        // Reset cin/cout
        std::cin.rdbuf(prev_cin);
        std::cout.rdbuf(prev_cout);

        // Check if the member is logged in
        REQUIRE(resultMember.getIsLoggedIn());

        // Check if the members vector has one more member
        REQUIRE(members.size() == 1);
    }

   SECTION("Display Borrowed Books") {
        // Create a member for testing
        Member testMember("Test Name", "", "test@email.com", "testpassword");
        members.push_back(testMember);

        // Redirect cout to stringstream to capture output
        std::stringstream output;

        std::streambuf* prev_cout = std::cout.rdbuf(output.rdbuf());

        // Perform display of borrowed books
        testMember.displayBorrowedBooks();

        // Reset cout
        std::cout.rdbuf(prev_cout);

        // Check if the output contains the member's name
        REQUIRE(output.str().find("Test Name") != std::string::npos);
    }
}
