#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>
#include <vector>
#include <UTKala.hpp>
#include <OutputHandler.hpp>
#include <define.hpp>
#include <map>

class UTKala;
class OutputHandler;

class CommandHandler {
public:
    CommandHandler() : utk(new UTKala()), oph(new OutputHandler()), isPOST(0) {
        commandArgs["signup"] = std::vector<ss>{"username", "password", "role", "address"};
        commandArgs["login"] = std::vector<ss>{"username", "password"};
        commandArgs["increase_credit"] = std::vector<ss>{"amount"};
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
    std::vector<ss> findArgs(std::vector<ss> argNames);
};

#endif
