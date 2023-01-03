#ifndef __UTKALA_HPP__
#define __UTKALA_HPP__

#include <string>
#include <vector>
#include <define.hpp>

class User;

class UTKala {
public:
    void signup(ss user, ss pass, ss city, ss role);
private:
    std::vector<User*> users;
};

#endif
