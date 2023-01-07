#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product {
public:
    Product(
        int id,
        std::string name,
        std::string seller_username,
        std::string category,
        std::string date,
        long long int price,
        int quantity
    );

    int getId() const;
    bool matchUsername(const std::string& username) const;
    bool matchPrice(int min, int max) const;
    long long int try_buy(int amount);
    long long int buy(int amount);
    std::string toString() const;

private:
    int id_;
    std::string name_;
    std::string seller_username_;
    std::string category_;
    std::string date_;
    long long int price_;
    int quantity_;
    int purchased_count_;
};

#endif
