#include <User.hpp>
#include <iostream>

int User::userEquals(ss user_, ss pass_) {
    return user == user_ && pass == pass_ ? 1 : user == user_ ? 2 : 3;
}
