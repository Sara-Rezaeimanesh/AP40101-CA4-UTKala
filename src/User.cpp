#include <User.hpp>
#include <iostream>
#include <Exceptions.hpp>

int User::userEquals(ss user_, ss pass_) {
    return user == user_ && pass == pass_ ? 1 : 
    user == user_ ? throw PermissionDeniedEx() : 0;
}
