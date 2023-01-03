#ifndef __SELLER_HPP__
#define __SELLER_HPP__

#include <string>
#include <User.hpp>
#include <vector>
#include <define.hpp>

class Seller : public User {
public:
    Seller(ss user, ss pass, ss city) : User(user, pass, city) {};
private:
};

#endif