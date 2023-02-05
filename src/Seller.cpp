#include "../include/Seller.hpp"

#include <algorithm>
#include <ctime>
#include <string>
#include <vector>

#include "../include/Exceptions.hpp"
#include "../include/Product.hpp"

bool Seller::ownProduct(Product* product) {
    return product->matchUsername(user);
}

long long int Seller::buyProduct(Product* to_buy, int amount, User* seller, bool diff_city) {
    throw BadRequestEx();
}

void Seller::refund(int purchase_id) {
    throw BadRequestEx();
}

Product* Seller::addProduct(
    const std::string& name, long long price, const std::string& category, int quantity, int refund
) {
    if (findProduct(name) != nullptr)
        throw BadRequestEx();

    auto curr_time = std::time(nullptr);
    Product* new_product = new Product(
        (User*)this,
        name,
        user,
        category,
        std::string(std::ctime(&curr_time)),
        price,
        quantity,
        refund
    );
    products_list_.push_back(new_product);

    return new_product;
}

void Seller::changeProductPrice(Product* product, long long new_price) {
    if (new_price < 0)
        throw BadRequestEx();

    product->changePrice(new_price);
}

Product* Seller::findProduct(const std::string& p_name) {
    for (const auto& p : products_list_)
        if (p->getName() == p_name)
            return p;
    return nullptr;
}

void Seller::showSubmittedProducts(bool sort, const std::string& sort_mode) const {
    if (products_list_.empty())
        std::cout << "Empty\n";

    // TODO check comp ordering in sort
    auto products_cpy = products_list_;
    if (sort) {
        if (sort_mode == "highest_price")
            std::sort(
                products_cpy.begin(), products_cpy.end(),
                [](const Product* p1, const Product* p2) { return p1->getPrice() < p2->getPrice(); }
            );
        else
            std::sort(
                products_cpy.begin(), products_cpy.end(),
                [](const Product* p1, const Product* p2) { return p1->getPrice() > p2->getPrice(); }
            );
    }
    for (const auto& product : products_list_) {
        std::cout << product->toString();
    }
}

void Seller::printRevenue() const {
    std::cout << "total revenue : " << credit_ << '\n';
}

Product* Seller::findProductById(const int id) {
    for (const auto& p : products_list_)
        if (p->getId() == id)
            return p;
    return nullptr;
}

void Seller::deleteItem(int id) {

    for (auto it = products_list_.begin(); it != products_list_.end(); ++it)
        if ((*it)->getId() == id) {
            products_list_.erase(it);
            return;
        }
    throw NotFoundEx();
}

void Seller::listTransactions() {
    if(transactions.size() == 0)
        throw EmptyEx();

    for(size_t i = 0; i < transactions.size(); i++) {
        std::cout << transactions[i]->to_string();
        if(i != transactions.size() - 1)
            std::cout << std::endl;
    }
}

void Seller::addTransaction(Product* to_buy, int amount, long long int deliveryCost,
                            long long int final_price, ss time_purchased, ss user) {
    Transaction* t = new Transaction(transactions.size(), to_buy, user,
                                         deliveryCost, final_price, amount, time_purchased);
    transactions.push_back(t);

}

ss Transaction::to_string() {
    return "id: " + std::to_string(id) + "\n" + "date: " + date + "buyer: " + buyer_name + "\n" +
            "item_id: " + std::to_string(product->getId()) + "\n" + "item_name: " + product->getName()+
            "\n" + "item_price: " + std::to_string(product->getPrice()) + "\n" + "purchased_count: " 
            + std::to_string(count) + "\n" + "delivery_cost: " + std::to_string(delivery) + "\n" + "total_cost: " +
            std::to_string(total_cost) + "\n";
}
