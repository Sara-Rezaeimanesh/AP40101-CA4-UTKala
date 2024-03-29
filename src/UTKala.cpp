#include "../include/UTKala.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "../include/Buyer.hpp"
#include "../include/Exceptions.hpp"
#include "../include/Product.hpp"
#include "../include/Seller.hpp"

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
    const std::string ADDR_ARG = "city";

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

void UTKala::logout(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();
    currUser = NULL;
}

void UTKala::increaseCredit(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

    const std::string AMOUNT_ARG = "amount";

    if (stoi(args[AMOUNT_ARG]) <= 0) throw BadRequestEx();
    currUser->changeCredit(stoi(args[AMOUNT_ARG]));
}

void UTKala::showWalletBallance(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

    currUser->showCredit();
}

void UTKala::showProducts(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

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

    if (sort_price) {
        std::sort(
            products.begin(), products.end(),
            [](const Product* p1, const Product* p2) {
                return p1->getId() < p2->getId();
            }
        );
    }
}

void UTKala::buyItem(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

    const std::string ID_ARG = "id";
    const std::string COUNT_ARG = "count";
    const std::string CITY_ARG = "city";

    bool diff_city = args.find(CITY_ARG) != args.end();

    Product* to_buy = nullptr;
    to_buy = findProduct(std::stoi(args[ID_ARG]));
    if (to_buy == nullptr)
        throw NotFoundEx();
    User* seller = findUser(to_buy->getSellerUsername());
    long long final_price = currUser->buyProduct(to_buy, std::stoi(args[COUNT_ARG]), seller, diff_city);
    to_buy->getOwner()->changeCredit(final_price);
    std::cout << "total_cost : " << final_price << '\n';
}

void UTKala::refund(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

    const std::string P_ID = "purchased_id";

    currUser->refund(std::stoi(args[P_ID]));
}

void UTKala::addProduct(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

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

void UTKala::printListPurchased(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

    currUser->printPurchased();
}

void UTKala::changeProductPrice(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

    const std::string PRICE_ARG = "price";
    const std::string ID_ARG = "id";

    Product* found_product = findProduct(std::stoi(args[ID_ARG]));
    if (found_product == nullptr)
        throw NotFoundEx();

    if (!currUser->ownProduct(found_product))
        throw PermissionDeniedEx();

    currUser->changeProductPrice(found_product, std::stoll(args[PRICE_ARG]));
}

void UTKala::showSubmittedProducts(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

    const std::string SORT_ARG = "sort_by";

    bool sort = args.find(SORT_ARG) != args.end();

    if (sort)
        currUser->showSubmittedProducts(sort, args[SORT_ARG]);
    else
        currUser->showSubmittedProducts();
}

void UTKala::printRevenue(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

    currUser->printRevenue();
}

void UTKala::deleteItem(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

    const std::string ID = "id";
    Product* found_prod = findProduct(std::stoi(args[ID]));
    if (found_prod == nullptr)
        throw NotFoundEx();
    if (!currUser->userNameMatches(found_prod->getOwner()->getUserName()))
        throw PermissionDeniedEx();
    products.erase(std::find(products.begin(), products.end(), found_prod));
    currUser->deleteItem(std::stoi(args[ID]));
    delete found_prod;
}

void UTKala::listTransactions(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

    currUser->listTransactions();
}

void UTKala::itemQuantity(ArgsMap args) {
    if (currUser == nullptr)
        throw BadRequestEx();

    const std::string ID = "id";
    const std::string QUANTITY = "quantity";

    if (stoi(args[QUANTITY]) < 0)
        throw BadRequestEx();

    for (auto p : products) {
        if (p->getId() == stoi(args[ID]) &&
            currUser->userNameMatches(p->getSellerUsername())) {
            p->changeQuantity(stoi(args[QUANTITY]));
            return;
        }

        else if (!currUser->userNameMatches(p->getSellerUsername()))
            throw PermissionDeniedEx();
    }
    throw NotFoundEx();
}