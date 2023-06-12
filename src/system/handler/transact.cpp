#include "../handler.h"

Handler::HandTransaction::HandTransaction(const Handler& thisHandler)
    : handler(const_cast<Handler&>(thisHandler)) {
}

/**
 * @brief Deposit money into an account
 *
 * @param account Account object
 * @param amount Amount to deposit
 * @param merchant Merchant name
 * @return int
 */
int Handler::HandTransaction::deposit(Account& account, double amount, std::string merchant) {
    if (amount <= 0) {
        // std::cerr << "[ERROR] Invalid amount" << std::endl;
        handler.account.update(account, account.id);
        return 1;
    }

    handler.account.update(account, account.id);

    double balance = account.balance.savings + amount;

    std::string check = "id = '" + account.id + "'";
    handler.database.update("accounts", {"savings"}, {std::to_string(balance)}, check);
    handler.account.update(account, account.id);

    return 0;
}

/**
 * @brief Withdraw money from an account
 *
 * @param account Account object
 * @param amount Amount to withdraw
 * @param merchant Merchant name
 * @return int
 */
int Handler::HandTransaction::withdraw(Account& account, double amount, std::string merchant) {
    if (amount <= 0) {
        // std::cerr << "[ERROR] Invalid amount" << std::endl;
        handler.account.update(account, account.id);
        return 1;
    }

    if (amount > account.balance.savings) {
        // std::cerr << "[ERROR] Amount is less than account savings" << std::endl;
        handler.account.update(account, account.id);
        return 2;
    }

    handler.account.update(account, account.id);

    double balance = account.balance.savings - amount;

    std::string check = "id = '" + account.id + "'";
    handler.database.update("accounts", {"savings"}, {std::to_string(balance)}, check);
    handler.account.update(account, account.id);

    return 0;
}

/**
 * @brief Transfer money between accounts
 *
 * @param account Account object
 * @param amount Amount to transfer
 * @param merchant Merchant name
 * @return int
 */
int Handler::HandTransaction::transfer(Account& account, std::string to_id, double amount, std::string merchant) {
    if (amount <= 0) {
        // std::cerr << "[ERROR] Invalid amount" << std::endl;
        return 1;
    }

    if (amount > account.balance.savings) {
        // std::cerr << "[ERROR] Amount is less than account savings" << std::endl;
        return 2;
    }

    if (to_id == account.id) {
        // std::cerr << "[ERROR] Cannot transfer to same account" << std::endl;
        return 3;
    }

    std::string check = "id = '" + to_id + "'";
    if (handler.database.select("loans", {"reference", "id", "type"}, check).size() <= 0) {
        // std::cerr << "[ERROR] Recipient account does not exist" << std::endl;
        return 4;
    }

    double balance;

    // User side
    handler.account.update(account, account.id);

    balance = account.balance.savings - amount;

    check = "id = '" + account.id + "'";
    handler.database.update("accounts", {"savings"}, {std::to_string(balance)}, check);

    // Recipient side
    handler.account.update(account, to_id);

    balance = account.balance.savings + amount;

    check = "id = '" + to_id + "'";
    handler.database.update("accounts", {"savings"}, {std::to_string(balance)}, check);

    // Return to user side
    handler.account.update(account, account.id);
    return 0;
}