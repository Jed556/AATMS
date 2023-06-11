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
        std::cout << "Login successful!" << std::endl;
        update(account, id);
        std::cout << "Logged in as " << account.name.user << std::endl;
        std::cout << "Account ID: " << account.id << std::endl;
        std::cout << "Name: " << account.name.first << " " << account.name.middle << " " << account.name.last << std::endl;
        // std::cout << "Name: " << account.name.first << " " << account.name.middle << " " << account.name.last << std::endl;
        // std::cout << "Username: " << account.name.user << std::endl;
        // std::cout << "CVC: " << account.cvc << std::endl;
        // std::cout << "PIN: " << account.pin << std::endl;
        // std::cout << "Expiry: " << account.expiry.month << "/" << account.expiry.year << std::endl;
        std::cout << "Loan Balance: " << account.balance.loan << std::endl;
        std::cout << "Savings Balance: " << account.balance.savings << std::endl;
        std::cout << "Created: " << account.date.created.toString("full") << std::endl;
        pause("\nPress enter to continue.");

        return 1;
    } else {
        std::cout << "Login failed. Please try again." << std::endl;

        return 0;
    }
}

/**
 * @brief Update account information
 *
 * @param account Account object to update
 * @param id Account ID to update from
 * @return int
 */
int Handler::HandAccount::update(Account& account, std::string id) {
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