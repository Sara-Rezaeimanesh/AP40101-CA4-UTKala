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

long long int Seller::buyProduct(Product* to_buy, int amount, bool diff_city) {
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
