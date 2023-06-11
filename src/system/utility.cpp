#include "handler.h"

void pause(std::string message) {
    if (message.empty()) message = "Press Enter to continue...";

    std::cout << message;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}