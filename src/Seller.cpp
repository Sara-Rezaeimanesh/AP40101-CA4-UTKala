#include "../include/Seller.hpp"

#include <ctime>
#include <string>
#include <vector>

#include "../include/Product.hpp"
#include "../include/Exceptions.hpp"

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
