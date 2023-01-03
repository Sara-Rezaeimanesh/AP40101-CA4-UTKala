#include <CommandHandler.hpp>
#include <iostream>
#include <sstream>
#include <exception>
using namespace std;

CommandHandler::~CommandHandler() {}

void CommandHandler::runInputs() {
    ss command;
    while(cin >> command)
        executeCommand(command);
}

int CommandHandler::executeCommand(ss command) {
    stringstream commandStream(command);
    bool stat = false;

    string type, name, qm, cpart;
    commandStream >> type >> name >> qm;
    while(commandStream >> cpart) 
        args.push_back(cpart);

    if(name == "signup")
        stat = handleSignUp();

    return stat;
}

vector<int> CommandHandler::findPos(vector<ss> argNames) {
    vector<int> pos;
    for(string argName : argNames) 
        for(size_t i = 0; i < args.size(); i++) {
            if(args[i] == argName) {
                pos.push_back(i+1);
                continue;
            }
            throw exception();
        }

    return pos;
}

bool CommandHandler::handleSignUp() {
    try {
        vector<int> argsPos = findPos(vector<ss>{"username", "password", "role", "city"});
        utk->signup(args[argsPos[0]], args[argsPos[1]], args[argsPos[2]], args[argsPos[3]]);

        return 1;
    } catch(std::exception& ex) { cout << "hello"; return 0; }
}