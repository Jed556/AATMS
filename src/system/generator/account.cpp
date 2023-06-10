#include "../generator.h"

// Function to generate a random 16-character account ID
std::string Generator::id() {
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int length = 16;
    std::string accountID;
    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % chars.length();
        accountID += chars[randomIndex];
    }
    return accountID;
}

/**
 * @brief Generate expiry year
 *
 * @return int Expiry year
 */
int Generator::expiryYear() {
    int year = getDate().year;
    int expiry = year + 4;
    return expiry;
}

/**
 * @brief Generate random cvc
 *
 * @return std::string CVC
 */
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