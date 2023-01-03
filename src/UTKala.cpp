#include <UTKala.hpp>
#include <Buyer.hpp>
#include <Seller.hpp>

void UTKala::signup(ss user, ss pass, ss city, ss role) {
    if(role == "buyer")
        users.push_back(new Buyer(user, pass, city));
    else
        users.push_back(new Seller(user, pass, city));
}
