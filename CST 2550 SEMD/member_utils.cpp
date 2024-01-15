// member_utils.cpp

#include "member.h"

// Define isMemberLoggedIn
bool Member::isMemberLoggedIn(const Member& member) {
    return member.getIsLoggedIn();
}

std::vector<Member> Member::loadMembersFromTxt()
{
    return std::vector<Member>();
}
