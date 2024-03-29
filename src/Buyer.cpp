#include "../include/Buyer.hpp"

#include <chrono>
#include <ctime>
#include <iostream>

#include "../include/Product.hpp"

bool Buyer::ownProduct(Product* product) {
    throw BadRequestEx();
}

void Buyer::showCredit() {
    std::cout << "wallet balance : " << credit_ << std::endl;
}

int Buyer::decideDeliveryPrice(bool diff_city) {
    return diff_city ? diff_city_shipping : same_city_shipping;
}

long long int Buyer::buyProduct(Product* to_buy, int amount, User* seller, bool diff_city) {
    // TODO handle different city being actually the same city
    Purchase new_purchase;

    new_purchase.total_cost = to_buy->tryBuy(amount);
    new_purchase.delivery_cost = decideDeliveryPrice(diff_city);

    int final_price = new_purchase.total_cost + new_purchase.delivery_cost;

    if (final_price > credit_)
        throw BadRequestEx();

    credit_ -= final_price;
    to_buy->buy(amount);
    new_purchase.bought_product = to_buy;
    new_purchase.amount = amount;
    new_purchase.id = purchase_list_.size() + 1;

    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    new_purchase.time_purchased = std::ctime(&end_time);

    purchase_list_.push_back(new_purchase);
    seller->addTransaction(to_buy, amount, decideDeliveryPrice(diff_city), final_price, new_purchase.time_purchased, user);

    return final_price;
}

void Buyer::refund(int purchase_id) {
    auto& found_purchase = find_purchase(purchase_id);
    found_purchase.bought_product->refund(found_purchase.amount);
    int refund_amount = found_purchase.bought_product->getRefund(found_purchase.total_cost);
    changeCredit(refund_amount);
    found_purchase.is_refunded = true;
    found_purchase.bought_product->getOwner()->changeCredit(refund_amount * -1);
}

Product* Buyer::addProduct(
    const std::string& name, long long price, const std::string& category, int quantity, int refund
) {
    throw BadRequestEx();
}

Buyer::Purchase& Buyer::find_purchase(int purchase_id) {
    for (auto& p : purchase_list_)
        if (p.id == purchase_id)
            return p;
    throw NotFoundEx();
}

void Buyer::printPurchased() {
    if (!purchase_list_.size())
        throw EmptyEx();

    for (Purchase p : purchase_list_)
        std::cout << "id : " << p.id << std::endl
                  << "date : " << p.time_purchased
                  << p.bought_product->stringInfoForPurchase() << std::endl
                  << "purchased_count : " << p.amount << std::endl
                  << "delivery_cost : " << p.delivery_cost << std::endl
                  << "total_cost : " << p.total_cost << std::endl;
}

void Buyer::changeProductPrice(Product* product, long long new_price) {
    throw BadRequestEx();
}

void Buyer::showSubmittedProducts(bool sort, const std::string& sort_mode) const {
    throw BadRequestEx();
}

void Buyer::printRevenue() const {
    throw BadRequestEx();
}
