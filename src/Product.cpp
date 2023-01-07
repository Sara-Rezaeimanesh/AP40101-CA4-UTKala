#include "../include/Product.hpp"

#include <sstream>
#include <string>

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
