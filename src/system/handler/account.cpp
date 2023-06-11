#include "../handler.h"

Handler::HandAccount::HandAccount(const Handler& thisHandler)
    : handler(const_cast<Handler&>(thisHandler)) {
}

int Handler::HandAccount::create(Account& account, Name name, std::string pin) {
    Generator generate(handler.UTC);
    int UTC = 8;
    account.id = generate.id();
    account.name = {name.first, name.middle, name.last, name.user};
    account.cvc = generate.cvc();
    account.pin = pin;
    account.expiry = {generate.getDate(UTC).month, generate.getDate(UTC).year};
    account.balance = {0.0, 0.0};
    account.date.created = generate.getDate(UTC);
    account.date.last = {{}, {}};

    handler.database.insert(
        "accounts",
        {"id", "first", "middle", "last", "user", "cvc", "pin", "month", "year", "loan", "savings", "created"},
        {account.id, account.name.first, account.name.middle, account.name.last, account.name.user, account.cvc, account.pin, std::to_string(account.expiry.month), std::to_string(account.expiry.year), std::to_string(account.balance.loan), std::to_string(account.balance.savings), account.date.created.toString("full")});
    return 0;
}