#ifndef __SELLER_HPP__
#define __SELLER_HPP__

#include <string>
#include <vector>

#include "User.hpp"
#include "define.hpp"

class Product;

class Seller : public User {
public:
    Seller(ss user, ss pass, ss city) : User(user, pass, city) {};

    bool ownProduct(Product* product);
    long long int buyProduct(Product* to_buy, int amount, bool diff_city = false);
    void refund(int purchase_id);
    Product* addProduct(
        const std::string& name, long long price, const std::string& category, int quantity, int refund
    );
    void changeProductPrice(Product* product, long long new_price);
    void showSubmittedProducts(bool sort = false, const std::string& sort_mode = "") const;

private:
    std::vector<Product*> products_list_;

    Product* findProduct(const std::string& p_name);
};

#endif