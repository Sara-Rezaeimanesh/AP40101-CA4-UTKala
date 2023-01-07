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
    void signup(std::vector<ss> args);
    void login(std::vector<ss> args);
    void logout();
    void inreseCredit(std::vector<ss> args);
    void showWalletBallance();
private:
    User* currUser;
    std::vector<User*> users;
    User* findUser(ss user);
    void checkUserExistsViolation(ss user_, ss pass_);
    void ckeckUserRoleIsValid(ss role);
};

#endif
