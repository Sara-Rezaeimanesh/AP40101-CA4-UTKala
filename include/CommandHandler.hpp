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
                       oph(new OutputHandler()),
                       isPOST(0) {
        commandArgs["signup"] = std::vector<ss> {"username", "password", "role", "address"};
        commandArgs["login"] = std::vector<ss> {"username", "password"};
        commandArgs["increase_credit"] = std::vector<ss> {"amount"};
        commandArgs["list_items"] = std::vector<ss> {"sort_by", "seller_username"};
        commandArgs["buy_item"] = std::vector<ss> {"id", "count", "city"};
        commandArgs["refund"] = std::vector<ss> {"purchase_id"};
    };
    ~CommandHandler();
    void runInputs();

private:
    UTKala* utk;
    OutputHandler* oph;
    std::vector<ss> args;
    std::map<ss, std::vector<ss>> commandArgs;
    /*in the next phase we must have three classe for each
        type of command GET, POST, DELETE and get rid
        of this atrocity!*/
    bool isPOST;

    void executeCommand(ss command);
    ss splitArgs(ss command);
    ArgsMap findArgs(std::vector<ss> argNames);
};

#endif
