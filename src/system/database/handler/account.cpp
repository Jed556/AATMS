#include "../handler.h"

Handler::HandAccount::HandAccount(const Handler& handler)
    : handler(const_cast<Handler&>(handler)) {
}

void Handler::HandAccount::create(Account& account, Name name, std::string pin) {
    account.set.id(generate.id());
    account.set.name(name.first, name.middle, name.last, name.user);
    account.set.cvc(generate.cvc());
    account.set.pin(pin);
    account.set.expiry(generate.getDate()[0], generate.getDate()[2]);
    account.set.balance(0.0, 0.0);
    account.set.date(generate.getDate(), {}, {});
}