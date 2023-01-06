#include <UTKala.hpp>
#include <Buyer.hpp>
#include <Seller.hpp>
#include <iostream>
#include <Exceptions.hpp>

using namespace std;

void UTKala::checkUserExistsViolation(ss user_, ss pass_) {
    try {
        User* u = findUser(user_, pass_);
        if(u) throw BadRequestEx();
    } catch(PermissionDeniedEx& ex) { throw BadRequestEx(); }
}

void UTKala::ckeckUserRoleIsValid(ss role) {
    if(role != "buyer" && role != "seller")
        throw BadRequestEx();
}

void UTKala::signup(vector<ss> args) {
    checkUserExistsViolation(args[user], args[pass]);
    ckeckUserRoleIsValid(args[role]);

    if(args[role] == "buyer")
        users.push_back(new Buyer(args[user], args[pass], args[city]));
    else
        users.push_back(new Seller(args[user], args[pass], args[city]));
}

void UTKala::login(vector<ss> args) {    
    currUser = findUser(args[user], args[pass]);
    if(!currUser) throw NotFoundEx();
}

User* UTKala::findUser(ss user, ss pass) {
    for(User* u : users) 
        if(u->userEquals(user, pass))
            return u;
    
    return NULL;
}

void UTKala::logout() {
    currUser = NULL;
}

void UTKala::inreseCredit(vector<ss> args) {
    if(stoi(args[0]) <= 0) throw BadRequestEx();
    currUser->increaseCredit(stoi(args[0]));
}

void UTKala::showWalletBallance() {
    currUser->showCredit();
}