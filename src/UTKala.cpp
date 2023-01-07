#include <Buyer.hpp>
#include <Exceptions.hpp>
#include <Seller.hpp>
#include <UTKala.hpp>
#include <iostream>

#include "../include/Product.hpp"

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

void UTKala::signup(vector<ss> args) {
    checkUserExistsViolation(args[user], args[pass]);
    checkUserRoleIsValid(args[role]);

    if (args[role] == "buyer")
        users.push_back(new Buyer(args[user], args[pass], args[city]));
    else
        users.push_back(new Seller(args[user], args[pass], args[city]));

    currUser = users[users.size() - 1];
}

void UTKala::login(vector<ss> args) {
    currUser = findUser(args[user]);
    if (!currUser) throw NotFoundEx();
    if (currUser->authenticates(args[pass])) return;
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

void UTKala::increaseCredit(vector<ss> args) {
    if (stoi(args[0]) <= 0) throw BadRequestEx();
    currUser->increaseCredit(stoi(args[0]));
}

void UTKala::showWalletBallance() {
    currUser->showCredit();
}

void UTKala::showProducts(
    bool filter_username, const std::string& username, bool filter_price, int min, int max
) {
    if (products.empty())
        std::cout << "Empty\n";
    for (const auto& product : products) {
        if (filter_username && !product->matchUsername(username))
            continue;
        if (filter_price && !product->matchPrice(min, max))
            continue;
        std::cout << product->toString();
    }
}

void UTKala::buyItem(int item_id, int count, bool diff_city) {
    Product* to_buy = nullptr;
    try {
        to_buy = findProduct(item_id);
        long long final_price = currUser->buyProduct(to_buy, count, diff_city);
        std::cout << "total_cost : " << final_price << '\n';
    }
    catch (const std::exception& e) {
        throw e;
    }
}
