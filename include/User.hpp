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
    void changeCredit(int amount) { credit_ += amount; }
    virtual bool ownProduct(Product* product) = 0;
    virtual void increaseCredit(int amount) { throw BadRequestEx(); };
    virtual void showCredit() { throw BadRequestEx(); }
    virtual long long int buyProduct(Product* to_buy, int amount, User* seller, bool diff_city = false) = 0;
    virtual void refund(int purchase_id) = 0;
    virtual Product* addProduct(
        const std::string& name, long long price, const std::string& category, int quantity, int refund
    ) = 0;
    virtual void printPurchased() { throw BadRequestEx(); }
    virtual void changeProductPrice(Product* product, long long new_price) = 0;
    virtual void showSubmittedProducts(bool sort = false, const std::string& sort_mode = "") const = 0;
    virtual void printRevenue() const = 0;
    virtual void deleteItem(int id) { throw BadRequestEx(); }
    virtual void listTransactions() { throw BadRequestEx(); }
    virtual void addTransaction(Product* to_buy, int amount, long long int deliveryCost,
                            long long int final_price, ss time_purchased, ss user) { throw BadRequestEx(); };

protected:
    ss user;
    ss pass;
    ss city;
    int credit_ = 0;
};

#endif
