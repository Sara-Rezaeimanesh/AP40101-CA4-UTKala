#ifndef __SELLER_HPP__
#define __SELLER_HPP__

#include <User.hpp>
#include <define.hpp>
#include <string>
#include <vector>

class Product;

class Seller : public User {
public:
    Seller(ss user, ss pass, ss city) : User(user, pass, city) {};

    long long int buyProduct(Product* to_buy, int amount, bool diff_city = false) { throw BadRequestEx(); };

private:
};

#endif