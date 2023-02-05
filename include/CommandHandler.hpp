#ifndef __USER_HPP__
#define __USER_HPP__

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "OutputHandler.hpp"
#include "UTKala.hpp"
#include "define.hpp"

using ArgsMap = std::unordered_map<std::string, std::string>;

class UTKala;
class OutputHandler;

class CommandHandler {
public:
    CommandHandler() : utk(new UTKala()),
                       oph(new OutputHandler()) {
        commands_list = {
            Command("signup", Command::CmdType::POST, {"username", "password", "role", "address"}, {}, utk, &UTKala::signup),
            Command("login", Command::CmdType::POST, {"username", "password"}, {}, utk, &UTKala::login),
            Command("logout", Command::CmdType::POST, {}, {}, utk, &UTKala::logout),
            Command("increase_credit", Command::CmdType::POST, {"amount"}, {}, utk, &UTKala::increaseCredit),
            Command("wallet_balance", Command::CmdType::GET, {}, {}, utk, &UTKala::showWalletBallance),
            Command("list_items", Command::CmdType::GET, {}, {"sort_by", "seller_username"}, utk, &UTKala::showProducts),
            Command("buy_item", Command::CmdType::POST, {"id", "count"}, {"city"}, utk, &UTKala::buyItem),
            Command("list_purchased", Command::CmdType::GET, {}, {}, utk, &UTKala::printListPurchased),
            Command("refund", Command::CmdType::POST, {"purchased_id"}, {}, utk, &UTKala::refund),
            Command("add_item", Command::CmdType::POST, {"name", "price", "category", "quantity"}, {"refund"}, utk, &UTKala::addProduct),
            Command("item_price", Command::CmdType::PUT, {"price", "id"}, {}, utk, &UTKala::changeProductPrice),
            Command("list_items", Command::CmdType::GET, {}, {"sort_by"}, utk, &UTKala::showSubmittedProducts),
            Command("revenue", Command::CmdType::GET, {}, {}, utk, &UTKala::printRevenue),
            Command("item", Command::CmdType::DELETE, {"id"}, {}, utk, &UTKala::deleteItem),
            Command("list_transactions", Command::CmdType::GET, {}, {}, utk, &UTKala::listTransactions),
            Command("item_quantity", Command::CmdType::PUT, {"id","quantity"}, {}, utk, &UTKala::itemQuantity)
        };
    };
    ~CommandHandler();
    void runInputs();

private:
    struct Command {
        enum class CmdType {
            POST,
            GET,
            PUT,
            DELETE,
            Undefined
        };

        using ArgsVec = std::vector<std::string>;
        using ExecPointer = void (UTKala::*)(ArgsMap);

        static Command::CmdType getType(const std::string& type_str);

        Command(
            const std::string& name,
            CmdType type,
            ArgsVec req_args,
            ArgsVec opt_args,
            UTKala* ut_kala,
            ExecPointer executer
        );

        void execute(ArgsMap args);
        bool isEqual(const std::string& name, CmdType type);

        std::string name_;
        CmdType type_;
        ArgsVec req_args_; // required args
        ArgsVec opt_args_; // optional args
        UTKala* ut_kala_;
        ExecPointer executer_; // the executer function

    private:
        bool checkRequiredArgs(const ArgsMap& args);

    private:
        bool hasGarbageArg(const ArgsMap& args);
    };

    UTKala* utk;
    OutputHandler* oph;

    std::vector<Command> commands_list;

    struct {
        std::vector<std::string> split_line;
        Command::CmdType cmd_type;
        ArgsMap args;
    } curr_command;

    std::vector<ss> OKCommand = {
        "signup", "login", "logout", "increase_credit", 
        "refund", "item", "item_price", "item_quantity"
    };

    void executeCommand(ss command);
    void parseCommand(std::string command);
    void splitCommand(const std::string& command);
    void findArgs(std::vector<std::string> argNames);
    bool isOKCommand(ss cname);
};

#endif
