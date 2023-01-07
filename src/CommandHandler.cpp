#include <CommandHandler.hpp>
#include <iostream>
#include <sstream>
#include <Exceptions.hpp>
using namespace std;

CommandHandler::~CommandHandler() {}

void CommandHandler::runInputs() {
    ss command;
    while(getline(cin, command)) 
        try {
            executeCommand(command);
            if(isPOST) oph->showStat("OK\n");
        } catch(std::exception& ex) { oph->showStat(ex.what()); }
}

ss CommandHandler::splitArgs(ss command) {
    stringstream commandStream(command);
    string type, name, qm, cpart;

    commandStream >> type >> name >> qm;
    while(commandStream >> cpart) 
        args.push_back(cpart);

    type == "POST" ? isPOST = 1 : isPOST = 0; 
    return name;
}

void CommandHandler::executeCommand(ss command) {
    ss name = splitArgs(command);

    if(name == "signup") 
        utk->signup(findArgs(commandArgs[name]));
    if(name == "login") 
        utk->login(findArgs(commandArgs[name]));
    if(name == "logout")
        utk->logout();
    if(name == "increase_credit")
        utk->increaseCredit(findArgs(commandArgs[name]));
    if(name == "wallet_balance")
        utk->showWalletBallance();

    args.clear();
}

vector<ss> CommandHandler::findArgs(vector<ss> argNames) {
    vector<ss> pos;
    for(string argName : argNames) 
        for(size_t i = 0; i < args.size(); i+=2) 
            if(args[i] == argName) {
                pos.push_back(args[i+1]);
                break;
            }
    
    if(argNames.size() != pos.size()) throw BadRequestEx();
    return pos;
}