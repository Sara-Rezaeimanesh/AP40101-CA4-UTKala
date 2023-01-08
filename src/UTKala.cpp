#include "UTKala.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "Buyer.hpp"
#include "Exceptions.hpp"
#include "Product.hpp"
#include "Seller.hpp"

using namespace std;

void UTKala::checkUserExistsViolation(ss user_, ss pass_) {
    User* u = findUser(user_);
    if (u) throw BadRequestEx();
}

void UTKala::checkUserRoleIsValid(ss role) {
    if (role != "buyer" && role != "seller")
        throw BadRequestEx();
}

Product* UTKala::findProduct(int item_id) {
    for (auto& product : products)
        if (product->getId() == item_id)
            return product;
    throw NotFoundEx();
}

void UTKala::signup(ArgsMap args) {
    const std::string USER_ARG = "username";
    const std::string PASS_ARG = "password";
    const std::string ROLE_ARG = "role";
    const std::string ADDR_ARG = "address";

    checkUserExistsViolation(args[USER_ARG], args[PASS_ARG]);
    checkUserRoleIsValid(args[ROLE_ARG]);

    if (args[ROLE_ARG] == "buyer")
        users.push_back(new Buyer(args[USER_ARG], args[PASS_ARG], args[ADDR_ARG]));
    else
        users.push_back(new Seller(args[USER_ARG], args[PASS_ARG], args[ADDR_ARG]));

    currUser = users.back();
}

void UTKala::login(ArgsMap args) {
    const std::string USER_ARG = "username";
    const std::string PASS_ARG = "password";

    currUser = findUser(args[USER_ARG]);
    if (!currUser) throw NotFoundEx();
    if (currUser->authenticates(args[PASS_ARG])) return;
    currUser = NULL;
    throw PermissionDeniedEx();
}

User* UTKala::findUser(ss user) {
    for (User* u : users)
        if (u->userNameMatches(user))
            return u;

    return NULL;
}

void UTKala::logout() {
    currUser = NULL;
}

void UTKala::increaseCredit(ArgsMap args) {
    const std::string AMOUNT_ARG = "amount";

    if (stoi(args[AMOUNT_ARG]) <= 0) throw BadRequestEx();
    currUser->increaseCredit(stoi(args[AMOUNT_ARG]));
}

void UTKala::showWalletBallance() {
    currUser->showCredit();
}

void UTKala::showProducts(ArgsMap args) {
    const std::string SELLER_ARG = "seller_username";
    const std::string SORT_ARG = "sort_by";

    if (products.empty()) {
        std::cout << "Empty\n";
        return;
    }

    bool filter_username = args.find(SELLER_ARG) != args.end();
    bool sort_price = args.find(SORT_ARG) != args.end();

    // TODO check ordering
    if (sort_price) {
        if (args[SORT_ARG] == "lowest_price") {
            std::sort(
                products.begin(), products.end(),
                [](const Product* p1, const Product* p2) {
                    return p1->getPrice() < p2->getPrice();
                }
            );
        }
        else {
            std::sort(
                products.begin(), products.end(),
                [](const Product* p1, const Product* p2) {
                    return p1->getPrice() > p2->getPrice();
                }
            );
        }
    }
    for (const auto& product : products) {
        if (filter_username && !product->matchUsername(args[SELLER_ARG]))
            continue;
        std::cout << product->toString();
    }
}

void UTKala::buyItem(ArgsMap args) {
    const std::string ID_ARG = "id";
    const std::string COUNT_ARG = "count";
    const std::string CITY_ARG = "city";

    bool diff_city = args.find(CITY_ARG) != args.end();

    Product* to_buy = nullptr;
    to_buy = findProduct(std::stoi(args[ID_ARG]));
    long long final_price = currUser->buyProduct(to_buy, std::stoi(args[COUNT_ARG]), diff_city);
    std::cout << "total_cost : " << final_price << '\n';

}

void UTKala::refund(ArgsMap args) {
    const std::string P_ID = "purchased_id";

    currUser->refund(std::stoi(args[P_ID]));
}

void UTKala::addProduct(ArgsMap args) {
    const std::string NAME_ARG = "name";
    const std::string PRICE_ARG = "price";
    const std::string CAT_ARG = "category";
    const std::string QUANTITY_ARG = "quantity";
    const std::string REFUND_ARG = "refund";

    int refund = (args.find(REFUND_ARG) == args.end()) ?
                     -1 :
                     std::stoi(args[REFUND_ARG]);

    int quantity = std::stoi(args[QUANTITY_ARG]);
    long long price = std::stoll(args[PRICE_ARG]);
    if (quantity < 0 || price < 0)
        throw BadRequestEx();
    if (refund < -1 || refund > 100)
        throw BadRequestEx();

    Product* new_product = currUser->addProduct(
        args[NAME_ARG],
        price,
        args[CAT_ARG],
        quantity,
        refund
    );
    products.push_back(new_product);
    std::cout << "id : " << new_product->getId() << '\n';
}

void UTKala::printListPurchased() {
    currUser->printPurchased();
}
