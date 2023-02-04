#ifndef __SELLER_HPP__
#define __SELLER_HPP__

#include <string>
#include <vector>

#include "User.hpp"
#include "define.hpp"

class Product;
class Transaction;

class Seller : public User {
public:
    Seller(ss user, ss pass, ss city) : User(user, pass, city) {};

    bool ownProduct(Product* product);
    long long int buyProduct(Product* to_buy, int amount, User* seller, bool diff_city = false);
    void refund(int purchase_id);
    Product* addProduct(
        const std::string& name, long long price, const std::string& category, int quantity, int refund
    );
    void changeProductPrice(Product* product, long long new_price);
    void showSubmittedProducts(bool sort = false, const std::string& sort_mode = "") const;
    void printRevenue() const;
    void deleteItem(int id);    
    void listTransactions();
    void addTransaction(Product* to_buy, int amount, long long int deliveryCost,
                            long long int final_price, ss time_purchased, ss user);

private:
    std::vector<Product*> products_list_;

    Product* findProduct(const std::string& p_name);
    Product* findProductById(int id);
    std::vector<Transaction*> transactions;
};

class Transaction {
public:
    Transaction(int id, Product* product, ss buyer_name, long long int delivery, 
            long long int total_cost, int count, ss date) : id(id), product(product), buyer_name(buyer_name), 
                delivery(delivery), total_cost(total_cost), count(count), date(date) {};
    ss to_string();
private:
    int id;
    Product* product;
    ss buyer_name;
    long long int delivery;
    long long int total_cost;
    int count;
    ss date;
};

#endif