#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>

#include "Exceptions.hpp"
#include "define.hpp"

class Product;

class User {
public:
    User() { user = "default"; };
    User(ss user, ss pass, ss city) : user(user),
                                      pass(pass),
                                      city(city) {};
    int userNameMatches(ss user_);
    ss toString() { return user + " " + pass + " " + city; }
    bool isDefault() { return user == "default"; }
    bool authenticates(ss pass_) { return pass == pass_; }
    virtual void increaseCredit(int amount) { throw BadRequestEx(); };
    virtual void showCredit() { throw BadRequestEx(); }
    virtual long long int buyProduct(Product* to_buy, int amount, bool diff_city = false) = 0;
    virtual void refund(int purchase_id) = 0;
    virtual Product* addProduct(
        const std::string& name, long long price, const std::string& category, int quantity, int refund
    ) = 0;

protected:
    ss user;
    ss pass;
    ss city;
};

#endif
