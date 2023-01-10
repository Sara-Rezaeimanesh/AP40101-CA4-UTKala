#include "CommandHandler.hpp"

#include <iostream>
#include <sstream>

#include "Exceptions.hpp"

using namespace std;

CommandHandler::~CommandHandler() {}

void CommandHandler::runInputs() {
    ss command;
    while (getline(cin, command))
        try {
            executeCommand(command);
            if (isPOST) oph->showStat("OK\n");
        }
        catch (std::exception& ex) {
            oph->showStat(ex.what());
        }
}

ss CommandHandler::splitArgs(ss command) {
    stringstream commandStream(command);
    string type, name, qm, cpart;

    commandStream >> type >> name >> qm;
    while (commandStream >> cpart)
        args.push_back(cpart);

    type == "POST" && name != "add_item" && name != "buy_item" 
    ? isPOST = 1 : isPOST = 0;
    return name;
}

void CommandHandler::executeCommand(ss command) {
    ss name = splitArgs(command);

    if (name == "signup")
        utk->signup(findArgs(commandArgs[name]));
    if (name == "login")
        utk->login(findArgs(commandArgs[name]));
    if (name == "logout")
        utk->logout();
    if (name == "increase_credit")
        utk->increaseCredit(findArgs(commandArgs[name]));
    if (name == "wallet_balance")
        utk->showWalletBallance();
    if (name == "list_items")
        utk->showProducts(findArgs(commandArgs[name]));
    if (name == "buy_item")
        utk->buyItem(findArgs(commandArgs[name]));
    if (name == "refund")
        utk->refund(findArgs(commandArgs[name]));
    if (name == "add_item")
        utk->addProduct(findArgs(commandArgs[name]));
    if (name == "list_purchased")
        utk->printListPurchased();
    if (name == "item_price")
        utk->changeProductPrice(findArgs(commandArgs[name]));

    args.clear();
}

ArgsMap CommandHandler::findArgs(vector<ss> argNames) {
    ArgsMap res_args;
    
    //TODO check for garbage keys
    for (std::size_t i = 0; i < args.size(); i += 2) {
        res_args[args[i]] = args[i + 1];
    }

    return res_args;
}