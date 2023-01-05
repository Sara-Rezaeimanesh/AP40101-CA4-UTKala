#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>
#include <define.hpp>

class User {
public:
    User(ss user, ss pass, ss city) : user(user), pass(pass), city(city) {};
    bool userEquals(ss user_, ss pass_);
    ss toString() {return user+" "+pass+" "+city;}
protected:
    ss user;
    ss pass;
    ss city;
};

#endif
