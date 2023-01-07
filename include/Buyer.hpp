#ifndef __BUYER_HPP__
#define __BUYER_HPP__

#include <string>

#include "User.hpp"
#include "define.hpp"

constexpr int diff_city_shipping = 2000;
constexpr int same_city_shipping = 1000;

class Buyer : public User {
public:
    Buyer(ss user, ss pass, ss city) : User(user, pass, city),
                                       credit(0) {};
    void increaseCredit(int amount);
    void showCredit();
    long long int buyProduct(Product* to_buy, int amount, bool diff_city = false);

private:
    int credit;
};

#endif