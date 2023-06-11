#include "handler.h"

void pause(std::string message) {
    if (message.empty()) message = "Press Enter to continue...";

    std::cout << message;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int confirm(std::string message) {
    std::string response;
    std::cout << message << " [y/n]" << std::endl;
    std::cout << ">> ";
    std::cin >> response;

    if (response == "y" || response == "Y" || response == "yes" || response == "Yes" || response == "YES")
        return 1;
    else if (response == "n" || response == "N" || response == "no" || response == "No" || response == "NO")
        return 0;

    std::cout << "[ERROR] Invalid response" << std::endl
              << std::endl;
    return confirm(message);
}