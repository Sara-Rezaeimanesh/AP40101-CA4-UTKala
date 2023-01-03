#ifndef __UTKALA_HPP__
#define __UTKALA_HPP__

#include <User.hpp>
#include <define.hpp>
#include <string>
#include <vector>

class UTKala {
public:
    int signup(ss user, ss pass, ss city, ss role);
private:
    std::vector<User*> users;
};

#endif
