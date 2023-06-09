#include "../handler.h"

/**
 * @brief Random ID generator
 *
 * @param withChars Include characters
 * @param length Length of ID
 * @return std::string
 */
std::string Generator::id(bool withChars, int length) {
    randomizeSeed();
    length = (length == 0) ? 16 : length;
    std::string chars = "0123456789";
    if (withChars) {
        chars += "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    }
    std::string accountID;
    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % chars.length();
        accountID += chars[randomIndex];
        // std::cout << "chars: " << chars << ", randomIndex: " << randomIndex << ", accountID: " << accountID << std::endl;
    }
    return accountID;
}

/**
 * @brief Generate expiry year
 *
 * @return int Expiry year
 */
int Generator::expiryYear() {
    DateTime date = getDate();
    int expiry = date.year + 4;
    return expiry;
}

/**
 * @brief Generate random cvc
 *
 * @return std::string CVC
 */
std::string Generator::cvc() {
    randomizeSeed();
    const std::string chars = "0123456789";
    const int length = 3;
    std::string cvc;
    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % chars.length();
        cvc += chars[randomIndex];
    }
    return cvc;
}