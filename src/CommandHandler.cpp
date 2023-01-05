#include <CommandHandler.hpp>
#include <iostream>
#include <sstream>
#include <exception>
using namespace std;

CommandHandler::~CommandHandler() {}

void CommandHandler::runInputs() {
    ss command;
    while(getline(cin, command)) {
        int stat = executeCommand(command);
        oph->showStat(stat);
    }
}

ss CommandHandler::splitArgs(ss command) {
    stringstream commandStream(command);
    string type, name, qm, cpart;

    commandStream >> type >> name >> qm;
    while(commandStream >> cpart) 
        args.push_back(cpart);

    return name;
}

int CommandHandler::executeCommand(ss command) {
    int stat = 0;
    ss name = splitArgs(command);

    try {
        if(name == "signup")
            stat = utk->signup(findArgs(commandArgs[name]));
        if(name == "login") 
            stat = utk->login(findArgs(commandArgs[name]));
        if(name == "logout")
            stat = utk->logout();

    } catch(std::exception& ex) { return 0; }

    return stat;
}

vector<ss> CommandHandler::findArgs(vector<ss> argNames) {
    vector<ss> pos;
    for(string argName : argNames) 
        for(size_t i = 0; i < args.size(); i+=2) 
            if(args[i] == argName) {
                pos.push_back(args[i+1]);
                break;
            }
    
    if(argNames.size() != pos.size()) throw exception();
    return pos;
}