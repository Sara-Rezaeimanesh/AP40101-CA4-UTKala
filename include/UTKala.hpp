#ifndef __UTKALA_HPP__
#define __UTKALA_HPP__

#include <string>
#include <unordered_map>
#include <vector>

#include "define.hpp"

using ArgsMap = std::unordered_map<std::string, std::string>;

class User;
class Product;

class UTKala {
public:
    void signup(ArgsMap args);
    void login(ArgsMap args);
    void logout();
    void increaseCredit(ArgsMap args);
    void showWalletBallance();
    void showProducts(ArgsMap args);
    void buyItem(ArgsMap args);

private:
    User* currUser;
    std::vector<User*> users;
    std::vector<Product*> products;
    User* findUser(ss user);
    void checkUserExistsViolation(ss user_, ss pass_);
    void checkUserRoleIsValid(ss role);
    Product* findProduct(int item_id);
};

#endif
