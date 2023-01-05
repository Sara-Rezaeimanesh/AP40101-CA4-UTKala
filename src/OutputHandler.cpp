#include <OutputHandler.hpp>
#include <iostream>

using namespace std;

void OutputHandler::showStat(int stat) {
    stat == 0 ? cout << "Bad Request\n" :
    stat == 3 ? cout << "Not Found\n" :
    stat == 2 ? cout << "Permission Denied\n" :
    cout << "OK\n" ; 
}