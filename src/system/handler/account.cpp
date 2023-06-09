#include "../handler.h"

Handler::HandAccount::HandAccount(const Handler& thisHandler)
    : handler(const_cast<Handler&>(thisHandler)) {
}

/**
 * @brief Create a new account
 *
 * @param account Account object
 * @param name Name object {first, middle, last, user}
 * @param pin 4-digit PIN
 * @return int
 */
int Handler::HandAccount::create(Account& account, Name name, std::string pin) {
    if (pin.length() != 4) {
        std::cerr << "[ERROR] Invalid PIN length" << std::endl;
        return 1;
    }

    std::string check, id;
    do {
        // std::cout << "Generating ID...";
        id = handler.generate.id(false, 16);
        check = "id = " + id;
        // std::cout << "[" << id << "]" << std::endl;
    } while (handler.database.select("accounts", {"id", "first", "middle", "last", "user"}, check).size() > 0);

    account.id = id;
    account.name = {name.first, name.middle, name.last, name.user};
    account.cvc = handler.generate.cvc();
    account.pin = pin;
    account.expiry = {handler.generate.getDate().month, handler.generate.getDate().year};
    account.balance = {0.0, 0.0};
    account.date.created = handler.generate.getDate();
    account.date.last = {{}, {}};

    handler.database.insert(
        "accounts",
        {"id", "first", "middle", "last", "user", "cvc", "pin", "month", "year", "loan", "savings", "created"},
        {account.id, account.name.first, account.name.middle, account.name.last, account.name.user, account.cvc, account.pin, std::to_string(account.expiry.month), std::to_string(account.expiry.year), std::to_string(account.balance.loan), std::to_string(account.balance.savings), account.date.created.toString("full")});

    return 0;
}

/**
 * @brief Login to an account
 *
 * @param username Username
 * @param pin 4-digit PIN
 * @return int
 */
int Handler::HandAccount::login(Account& account, std::string id, std::string pin) {
    std::string check = "id = '" + id + "' AND pin = '" + pin + "'";
    if (handler.database.select("accounts", {"id", "first", "middle", "last", "user", "pin"}, check).size() > 0) {
        update(account, id);
        return 0;
    } else {
        // std::cerr << "Login failed. Please try again." << std::endl;
        return 1;
    }
}

int Handler::HandAccount::logout(Account& account) {
    account = {};
    // std::cout << "Logged out successfully!" << std::endl;

    return 0;
}

int Handler::HandAccount::edit(Account& account) {
    std::string check = "id = " + account.id;
    handler.database.update("accounts", {"first", "middle", "last", "user", "pin"}, {account.name.first, account.name.middle, account.name.last, account.name.user, account.pin}, check);

    return 0;
}

/**
 * @brief Update account information
 *
 * @param account Account object to update
 * @param id Account ID to update from
 * @return int
 */
int Handler::HandAccount::update(struct Account& account, std::string id) {
    DateTime convert;
    std::string check = "id = " + id;
    std::vector<std::string> data = handler.database.select("accounts", {"id", "first", "middle", "last", "user", "cvc", "pin", "month", "year", "loan", "savings", "created"}, check)[0].columnValues;

    account.id = data[0];
    account.name = {data[1], data[2], data[3], data[4]};
    account.cvc = data[5];
    account.pin = data[6];
    account.expiry = {std::stoi(data[7]), std::stoi(data[8])};
    account.balance = {std::stod(data[9]), std::stod(data[10])};
    account.date.created = convert.fromString(data[11]);

    return 0;
}

/**
 * @brief Delete an account
 *
 * @param id Account ID to delete
 * @return int
 */
int Handler::HandAccount::remove(std::string id) {
    std::string check = "id = " + id;
    if (handler.database.select("accounts", {"id"}, check).size() > 0) {
        handler.database.remove("accounts", check);
        // std::cout << "Account deleted!" << std::endl;
        return 0;
    } else {
        // std::cerr << "[ERROR] Account not found." << std::endl;
        return 1;
    }
}