#include "../include/Product.hpp"

#include <sstream>
#include <string>

#include "../include/Exceptions.hpp"

static int last_used_id = 0;

Product::Product(
    std::string name,
    std::string seller_username,
    std::string category,
    std::string date,
    long long int price,
    int quantity,
    int refund_percentage
) : id_(++last_used_id),
    name_(name),
    seller_username_(seller_username),
    category_(category),
    date_(date),
    price_(price),
    quantity_(quantity),
    purchased_count_(0),
    refund_percentage_(refund_percentage) {}

std::string Product::getName() const {
    return name_;
}

int Product::getId() const { return id_; }

long long int Product::getPrice() const { return price_; }

int Product::getRefund(int spent_credit) const {
    return (spent_credit * refund_percentage_) / 100;
}

bool Product::matchUsername(const std::string& username) const {
    return seller_username_ == username;
}

long long int Product::tryBuy(int amount) {
    if (amount > quantity_)
        throw BadRequestEx();
    return price_ * amount;
}

long long int Product::buy(int amount) {
    long long int final_price = tryBuy(amount);
    quantity_ -= amount;
    return final_price;
}

void Product::refund(int amount) {
    if (refund_percentage_ == -1)
        throw BadRequestEx();

    quantity_ += amount;
}

void Product::changePrice(int new_price) {
    price_ = new_price;
}

std::string Product::toString() const {
    std::ostringstream stream;
    stream << "id : " << id_ << '\n';
    stream << "name : " << name_ << '\n';
    stream << "seller : " << seller_username_ << '\n';
    stream << "category : " << category_ << '\n';
    stream << "date : " << date_;
    stream << "price : " << price_ << '\n';
    stream << "quantity : " << quantity_ << '\n';
    stream << "purchased_count : " << purchased_count_ << '\n';
    return stream.str();
}

std::string  Product::stringInfoForPurchase() const {
    return "seller : " + seller_username_ + "\n"
                + "item_id : " + std::to_string(id_) + "\n"
                + "item_name : " + name_ + "\n" 
                + "item_price : " + std::to_string(price_);

}
