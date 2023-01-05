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

int CommandHandler::executeCommand(ss command) {
    stringstream commandStream(command);
    bool stat = false;

    string type, name, qm, cpart;
    commandStream >> type >> name >> qm;
    while(commandStream >> cpart) 
        args.push_back(cpart);

    try {
        if(name == "signup")
            stat = utk->signup(findArgs(commandArgs[name]));
        if(name == "login")
            stat = utk->login(findArgs(commandArgs[name]));
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