#include <UTKala.hpp>
#include <Buyer.hpp>
#include <Seller.hpp>
#include <iostream>

using namespace std;

int UTKala::signup(vector<ss> args) {
    if(args[role] == "buyer")
        users.push_back(new Buyer(args[user], args[pass], args[city]));
    else
        users.push_back(new Seller(args[user], args[pass], args[city]));

    return 1;
}

int UTKala::login(vector<ss> args) {
    try {
        currUser = findUser(args[user], args[pass]);
        return 1;
    } catch(std::exception& ex) { return stoi(ex.what()); }
}

User* UTKala::findUser(ss user, ss pass) {
    for(User* u : users) {
        int equals = u->userEquals(user, pass);
        if(equals == 1)
            return u;
        throw runtime_error(to_string(equals));
    }
    return NULL;
}

int UTKala::logout() {
    currUser = NULL;
    return 1;
}