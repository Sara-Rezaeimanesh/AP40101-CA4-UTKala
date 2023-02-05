#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class User;

class Product {
public:
    Product(
        User* owner,
        std::string name,
        std::string seller_username,
        std::string category,
        std::string date,
        long long int price,
        int quantity,
        int refund_percentage = -1
    );

    std::string getName() const;
    std::string getSellerUsername() const { return seller_username_; };
    int getId() const;
    long long int getPrice() const;
    int getRefund(int spent_credit) const;
    User* getOwner() const;
    bool matchUsername(const std::string& username) const;
    long long int tryBuy(int amount);
    long long int buy(int amount);
    void refund(int amount);
    void changePrice(int new_price);
    std::string toString() const;
    std::string  stringInfoForPurchase() const;
    void changeQuantity(int quantity);

private:
    User* owner_;
    int id_;
    std::string name_;
    std::string seller_username_;
    std::string category_;
    std::string date_;
    long long int price_;
    int quantity_;
    int purchased_count_;

    int refund_percentage_;
};

#endif
