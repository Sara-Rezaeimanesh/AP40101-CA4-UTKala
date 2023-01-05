#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>
#include <vector>
#include <UTKala.hpp>
#include <OutputHandler.hpp>
#include <define.hpp>

class UTKala;
class OutputHandler;

class CommandHandler {
public:
    CommandHandler() : utk(new UTKala()), oph(new OutputHandler()) {};
    ~CommandHandler();
    void runInputs();
private:
    UTKala* utk;
    OutputHandler* oph;
    std::vector<ss> args;
    int executeCommand(ss command);
    int handleSignUp();
    std::vector<int> findPos(std::vector<ss> argNames);
};

#endif
