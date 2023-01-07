#include <Buyer.hpp>
#include <iostream>

#include "../include/Product.hpp"

void Buyer::increaseCredit(int amount) {
    credit += amount;
}

void Buyer::showCredit() {
    std::cout << "wallet balance : " << credit << std::endl;
}

long long int Buyer::buyProduct(Product* to_buy, int amount, bool diff_city) {
    int final_price = 0;
    try {
        final_price = to_buy->try_buy(amount);
    }
    catch (const std::exception& e) {
        throw e;
    }

    if (diff_city)
        final_price += diff_city_shipping;
    else
        final_price += same_city_shipping;

    if (final_price > credit)
        throw BadRequestEx();
        
    credit -= final_price;
    to_buy->buy(amount);
    return final_price;
}
