#ifndef __BUYER_HPP__
#define __BUYER_HPP__

#include <string>
#include <User.hpp>
#include <define.hpp>

class Buyer : public User {
public:
    Buyer(ss user, ss pass, ss city) : User(user, pass, city) {};
private:

};

#endif