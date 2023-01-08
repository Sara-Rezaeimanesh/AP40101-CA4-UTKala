#ifndef __BUYER_HPP__
#define __BUYER_HPP__

#include <string>
#include <vector>

#include "User.hpp"
#include "define.hpp"

constexpr int diff_city_shipping = 2000;
constexpr int same_city_shipping = 1000;

class Buyer : public User {
public:
    Buyer(ss user, ss pass, ss city) : User(user, pass, city),
                                       credit_(0) {};
    void increaseCredit(int amount);
    void showCredit();
    long long int buyProduct(Product* to_buy, int amount, bool diff_city = false);
    void refund(int purchase_id);
    Product* addProduct(
        const std::string& name, long long price, const std::string& category, int quantity, int refund
    );
    void printPurchased();

private:
    struct Purchase {
        Product* bought_product;
        int amount;
        int id;
        bool is_refunded = false;
        ss time_purchased;
        int total_cost;
        int delivery_cost;
    };

    int credit_;
    std::vector<Purchase> purchase_list_;

    Purchase& find_purchase(int purchase_id);
    int decideDeliveryPrice(bool diff_city);
};

#endif