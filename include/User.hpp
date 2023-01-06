#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>
#include <define.hpp>
#include <Exceptions.hpp>

class User {
public:
    User() { user = "default"; };
    User(ss user, ss pass, ss city) : user(user), pass(pass), city(city) {};
    int userEquals(ss user_, ss pass_);
    ss toString() {return user+" "+pass+" "+city;}
    bool isDefault() { return user =="default"; }
    virtual void increaseCredit(int amount) { throw BadRequestEx(); };
    virtual void showCredit() { throw BadRequestEx(); }
protected:
    ss user;
    ss pass;
    ss city;
};

#endif
