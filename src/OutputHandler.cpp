#include <OutputHandler.hpp>
#include <iostream>

using namespace std;

void OutputHandler::showStat(int stat) {
    stat == 1 ? cout << "OK\n" :
    stat == 0 ? cout << "Bad Request\n" :
    cout << "Not Found\n" ; 
}