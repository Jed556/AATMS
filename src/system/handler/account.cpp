#include "../handler.h"

Handler::HandAccount::HandAccount(const Handler& thisHandler)
    : thisHandler(const_cast<Handler&>(thisHandler)) {
}

void Handler::HandAccount::create(Account& account, Name name, std::string pin) {
    Generator generate;
    account.id = generate.id();
    account.name = {name.first, name.middle, name.last, name.user};
    account.cvc = generate.cvc();
    account.pin = pin;
    account.expiry = {generate.getDate().month, generate.getDate().year};
    account.balance = {0.0, 0.0};
    account.date = {generate.getDate()};
    account.date.last = {{}, {}};

    thisHandler.database.insert("accounts",
                                {"id", "first", "middle", "last", "user", "cvc", "pin", "month", "year", "loan", "savings", "created", "login", "logout"},
                                {account.id, account.name.first, account.name.middle, account.name.last, account.name.user, account.cvc, account.pin, std::to_string(account.expiry.month), std::to_string(account.expiry.year), std::to_string(account.balance.loan), std::to_string(account.balance.savings), account.date.created.toString(), account.date.last.login.toString(), account.date.last.logout.toString()});
}