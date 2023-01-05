#ifndef __UTKALA_HPP__
#define __UTKALA_HPP__

#include <string>
#include <vector>
#include <define.hpp>

class User;

class UTKala {
public:
    void signup(ss user, ss pass, ss role, ss city);
private:
    User* currUser;
    std::vector<User*> users;
};

#endif
