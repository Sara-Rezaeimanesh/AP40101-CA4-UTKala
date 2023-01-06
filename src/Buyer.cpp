#include <Buyer.hpp>
#include <iostream>

void Buyer::increaseCredit(int amount) {
    credit += amount;
}

void Buyer::showCredit() {
    std::cout << "wallet balance : " << credit << std::endl; 
}
