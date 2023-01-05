#include <OutputHandler.hpp>
#include <iostream>

using namespace std;

void OutputHandler::showStat(int stat) {
    stat ? cout << "OK\n" : cout << "Bad Request\n"; 
}