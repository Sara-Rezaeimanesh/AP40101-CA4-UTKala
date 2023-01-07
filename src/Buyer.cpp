#include <Buyer.hpp>
#include <iostream>

#include "Product.hpp"

void Buyer::increaseCredit(int amount) {
    credit_ += amount;
}

void Buyer::showCredit() {
    std::cout << "wallet balance : " << credit_ << std::endl;
}

long long int Buyer::buyProduct(Product* to_buy, int amount, bool diff_city) {
    // TODO handle different city being actually the same city
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

    if (final_price > credit_)
        throw BadRequestEx();

    credit_ -= final_price;
    to_buy->buy(amount);
    Purchase new_purchase;
    new_purchase.bought_product = to_buy;
    new_purchase.amount = amount;
    new_purchase.id = purchase_list_.back().id + 1;

    purchase_list_.push_back(new_purchase);

    return final_price;
}

void Buyer::refund(int purchase_id) {
    try {
        auto& found_purchase = find_purchase(purchase_id);
        credit_ += found_purchase.bought_product->refund(found_purchase.amount);
        found_purchase.is_refunded = true;
    }
    catch (const std::exception& e) {
        throw e;
    }
}

Buyer::Purchase& Buyer::find_purchase(int purchase_id) {
    for (auto& p : purchase_list_)
        if (p.id == purchase_id)
            return p;
    throw NotFoundEx();
}
