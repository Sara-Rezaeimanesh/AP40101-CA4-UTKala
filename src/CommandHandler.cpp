#include "../include/CommandHandler.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "../include/Exceptions.hpp"

using namespace std;

CommandHandler::~CommandHandler() {}

void CommandHandler::runInputs() {
    ss command;
    while (getline(cin, command))
        try {
            executeCommand(command);
        }
        catch (std::exception& ex) {
            oph->showStat(ex.what());
        }
}
CommandHandler::Command::CmdType CommandHandler::Command::getType(const std::string& type_str) {
    if (type_str == "POST")
        return CommandHandler::Command::CmdType::POST;
    if (type_str == "PUT")
        return CommandHandler::Command::CmdType::PUT;
    if (type_str == "DELETE")
        return CommandHandler::Command::CmdType::DELETE;
    if (type_str == "GET")
        return CommandHandler::Command::CmdType::GET;

    return CommandHandler::Command::CmdType::Undefined;
}

CommandHandler::Command::Command(
    const std::string& name,
    CmdType type,
    ArgsVec req_args,
    ArgsVec opt_args,
    UTKala* ut_kala,
    ExecPointer executer
)
    : name_(name),
      type_(type),
      req_args_(req_args),
      opt_args_(opt_args),
      ut_kala_(ut_kala),
      executer_(executer) {}

void CommandHandler::Command::execute(ArgsMap args) {
    if (!checkRequiredArgs(args))
        throw BadRequestEx();
    if (hasGarbageArg(args))
        throw BadRequestEx();
    (ut_kala_->*executer_)(args);
}

bool CommandHandler::Command::isEqual(const std::string& name, CmdType type) {
    return type_ == type && name_ == name;
}

bool CommandHandler::Command::checkRequiredArgs(const ArgsMap& args) {
    for (const auto& req_arg : req_args_)
        if (args.find(req_arg) == args.end())
            return false;
    return true;
}

bool CommandHandler::Command::hasGarbageArg(const ArgsMap& args) {
    for (const auto& arg_pair : args) {
        if (std::find(req_args_.begin(), req_args_.end(), arg_pair.first) != req_args_.end())
            continue;
        if (std::find(opt_args_.begin(), opt_args_.end(), arg_pair.first) != opt_args_.end())
            continue;
        return true;
    }
    return false;
}

void CommandHandler::parseCommand(std::string command) {
    const int TYPE_IDX = 0;
    const int ARGS_START_IDX = 3;

    splitCommand(command);
    curr_command.cmd_type = Command::getType(curr_command.split_line[TYPE_IDX]);
    std::vector<std::string> args_vec;
    if (curr_command.split_line.size() > 3)
        args_vec = std::vector<std::string>(
            curr_command.split_line.begin() + ARGS_START_IDX, curr_command.split_line.end()
        );
    findArgs(args_vec);
}

void CommandHandler::splitCommand(const std::string& command) {
    curr_command.split_line.clear();
    std::istringstream cmd_stream(command);
    std::string temp;
    while (cmd_stream >> temp)
        curr_command.split_line.push_back(temp);
}

bool CommandHandler::isOKCommand(ss cname) {
    for(ss name : OKCommand)
        if(name == cname)
            return true;
    return false;
}

void CommandHandler::executeCommand(ss command) {
    const int NAME_IDX = 1;

    cout << "this is comamnd: " << command << endl;

    parseCommand(command);
    for (auto& cmd : commands_list) {
        if (cmd.isEqual(curr_command.split_line[NAME_IDX], curr_command.cmd_type)) {
            cmd.execute(curr_command.args);
            if(isOKCommand(curr_command.split_line[NAME_IDX]))
                std::cout << "OK\n";
            return;
        }
    }
    throw BadRequestEx();
}

void CommandHandler::findArgs(vector<ss> argNames) {
    curr_command.args.clear();
    for (std::size_t i = 0; i < argNames.size(); i += 2)
        curr_command.args[argNames[i]] = argNames[i + 1];
}

