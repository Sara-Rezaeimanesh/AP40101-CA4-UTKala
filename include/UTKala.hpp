#ifndef __UTKALA_HPP__
#define __UTKALA_HPP__

#include <string>
#include <vector>
#include <define.hpp>

enum signupArgs {
    user, pass, role, city
};

class User;

class UTKala {
public:
    int signup(std::vector<ss> args);
    int login(std::vector<ss> args);
    int logout();
private:
    User* currUser;
    std::vector<User*> users;
    User* findUser(ss user, ss pass);
};

#endif
