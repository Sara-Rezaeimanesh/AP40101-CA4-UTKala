#include <UTKala.hpp>
#include <Buyer.hpp>
#include <Seller.hpp>
#include <iostream>

using namespace std;

void UTKala::signup(ss user, ss pass, ss role, ss city) {
    if(role == "buyer")
        users.push_back(new Buyer(user, pass, city));
    else
        users.push_back(new Seller(user, pass, city));
}
