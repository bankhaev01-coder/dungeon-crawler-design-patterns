#include "ConsoleObserver.h"
#include <iostream>

void ConsoleObserver::update(const std::string& event) {
    std::cout << "[EVENT] " << event << std::endl;
}