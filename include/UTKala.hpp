#ifndef __UTKALA_HPP__
#define __UTKALA_HPP__

#include <define.hpp>
#include <string>
#include <vector>

enum signupArgs {
    user,
    pass,
    role,
    city
};

class User;
class Product;

class UTKala {
public:
    void signup(std::vector<ss> args);
    void login(std::vector<ss> args);
    void logout();
    void increaseCredit(std::vector<ss> args);
    void showWalletBallance();
    void showProducts(
        bool filter_username, const ss& username, bool filter_price, int min, int max
    );

private:
    User* currUser;
    std::vector<User*> users;
    std::vector<Product*> products;
    User* findUser(ss user);
    void checkUserExistsViolation(ss user_, ss pass_);
    void checkUserRoleIsValid(ss role);
};

#endif
