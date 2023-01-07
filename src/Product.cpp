#include "../include/Product.hpp"

#include <sstream>
#include <string>

#include "../include/Exceptions.hpp"

Product::Product(
    int id,
    std::string name,
    std::string seller_username,
    std::string category,
    std::string date,
    long long int price,
    int quantity
) : id_(id),
    name_(name),
    seller_username_(seller_username),
    category_(category),
    date_(date),
    price_(price),
    quantity_(quantity),
    purchased_count_(0) {}

int Product::getId() const { return id_; }

bool Product::matchUsername(const std::string& username) const {
    return seller_username_ == username;
}

bool Product::matchPrice(int min, int max) const {
    return price_ <= max && price_ >= min;
}

long long int Product::try_buy(int amount) {
    if (amount > quantity_)
        throw BadRequestEx();
    return price_ * amount;
}

long long int Product::buy(int amount) {
    long long int final_price = try_buy(amount);
    quantity_ -= amount;
    return final_price;
}

std::string Product::toString() const {
    std::ostringstream stream;
    stream << "id : " << id_ << '\n';
    stream << "name : " << name_ << '\n';
    stream << "seller : " << seller_username_ << '\n';
    stream << "category : " << category_ << '\n';
    stream << "date : " << date_ << '\n';
    stream << "price : " << price_ << '\n';
    stream << "quantity : " << quantity_ << '\n';
    stream << "purchased_count : " << purchased_count_ << '\n';
    return stream.str();
}
