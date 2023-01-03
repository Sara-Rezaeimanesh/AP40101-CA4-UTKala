#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>
#include <vector>
#include <UTKala.hpp>
#include <define.hpp>

class CommandHandler {
public:
    CommandHandler(){ utk = new UTKala(); };
    ~CommandHandler();
    void runInputs();
private:
    UTKala* utk;
    std::vector<ss> args;
    int executeCommand(ss command);
    bool handleSignUp();
    std::vector<int> findPos(std::vector<ss> argNames);
};

#endif
