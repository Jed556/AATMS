#include "../generator.h"

// Function to generate a random 16-character account ID
std::string Generator::accountID() {
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int length = 16;
    std::string accountID;
    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % chars.length();
        accountID += chars[randomIndex];
    }
    return accountID;
}

// Function to generate a random expiration month (01-12)
std::string Generator::expirationMonth() {
    int randomMonth = rand() % 12 + 1;
    return (randomMonth < 10) ? "0" + std::to_string(randomMonth) : std::to_string(randomMonth);
}

// Function to generate a random expiration year (2023-2033)
std::string Generator::expirationYear() {
    int randomYear = rand() % 11 + 2023;
    return std::to_string(randomYear);
}

// Function to generate a random 3-character CVC
std::string Generator::cvc() {
    const std::string chars = "0123456789";
    const int length = 3;
    std::string cvc;
    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % chars.length();
        cvc += chars[randomIndex];
    }
    return cvc;
}