#ifndef __SELLER_HPP__
#define __SELLER_HPP__

#include <string>
#include <vector>

#include "User.hpp"
#include "define.hpp"

class Product;

class Seller : public User {
public:
    Seller(ss user, ss pass, ss city) : User(user, pass, city) {};

    long long int buyProduct(Product* to_buy, int amount, bool diff_city = false) { throw BadRequestEx(); };

private:
};

#endif