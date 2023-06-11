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
        std::cout << "Invalid PIN length. Please try again." << std::endl;
        return 1;
    }

    std::string check, id;
    do {
        std::cout << "Generating ID...";
        id = handler.generate.id(false, 16);
        check = "id = " + id;
        std::cout << "[" << id << "]" << std::endl;
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