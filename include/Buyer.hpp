#ifndef __BUYER_HPP__
#define __BUYER_HPP__

#include <string>
#include <User.hpp>
#include <define.hpp>

class Buyer : public User {
public:
    Buyer(ss user, ss pass, ss city) : User(user, pass, city), credit(0) {};
    void increaseCredit(int amount);
    void showCredit();
private:
    int credit;

};

#endif