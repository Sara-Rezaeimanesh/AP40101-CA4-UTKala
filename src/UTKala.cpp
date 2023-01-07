#include <UTKala.hpp>
#include <Buyer.hpp>
#include <Seller.hpp>
#include <iostream>
#include <Exceptions.hpp>

using namespace std;

void UTKala::checkUserExistsViolation(ss user_, ss pass_) {
    User* u = findUser(user_);
    if(u) throw BadRequestEx();
}

void UTKala::checkUserRoleIsValid(ss role) {
    if(role != "buyer" && role != "seller")
        throw BadRequestEx();
}

void UTKala::signup(vector<ss> args) {
    checkUserExistsViolation(args[user], args[pass]);
    checkUserRoleIsValid(args[role]);

    if(args[role] == "buyer")
        users.push_back(new Buyer(args[user], args[pass], args[city]));
    else
        users.push_back(new Seller(args[user], args[pass], args[city]));

    currUser = users[users.size()-1];
}

void UTKala::login(vector<ss> args) {    
    currUser = findUser(args[user]);
    if(!currUser) throw NotFoundEx();
    if(currUser->authenticates(args[pass])) return;
    currUser = NULL;
    throw PermissionDeniedEx(); 
}

User* UTKala::findUser(ss user) {
    for(User* u : users) 
        if(u->userNameMatches(user))
            return u;
    
    return NULL;
}

void UTKala::logout() {
    currUser = NULL;
}

void UTKala::increaseCredit(vector<ss> args) {
    if(stoi(args[0]) <= 0) throw BadRequestEx();
    currUser->increaseCredit(stoi(args[0]));
}

void UTKala::showWalletBallance() {
    currUser->showCredit();
}