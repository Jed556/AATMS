#include "../schema.h"

/**
 * @brief Construct new Account object
 *
 */
Account::Account(bool create)
    : create(create), set(*this), get(*this), generate(generate) {
}

/**
 * @brief Construct new Account::Set object
 *
 * @param account Account object
 */
Account::Set::Set(const Account& account)
    : account(const_cast<Account&>(account)) {
}

/**
 * @brief Construct new Account::Get object
 *
 * @param account Account object
 */
Account::Get::Get(const Account& account)
    : account(const_cast<Account&>(account)) {
}

/**
 * @brief Set account id
 *
 * @param id Account id
 */
void Account::Set::id(std::string id) {
    account.id = id;
}

/**
 * @brief Set account name
 *
 * @param first First name
 * @param middle Middle name
 * @param last Last name
 */
void Account::Set::name(std::string first, std::string middle, std::string last, std::string user) {
    account.name.first = first;
    account.name.middle = middle;
    account.name.last = last;
    account.name.user = user;
}

/**
 * @brief Set account cvc
 *
 * @param cvc Account cvc
 */
void Account::Set::cvc(std::string cvc) {
    account.cvc = cvc;
}

/**
 * @brief Set account pin
 *
 * @param pin Account pin
 */
void Account::Set::pin(std::string pin) {
    account.pin = pin;
}

/**
 * @brief Set account expiry
 *
 * @param expiry Account expiry
 */
void Account::Set::expiry(int month, int year) {
    account.expiry.month = month;
    account.expiry.year = year;
}

/**
 * @brief Set account balance
 *
 * @param loan Account loan balance
 * @param savings Account savings balance
 */
void Account::Set::balance(double loan, double savings) {
    account.balance.loan = loan;
    account.balance.savings = savings;
}

/**
 * @brief Set account date
 *
 * @param created Account created date
 * @param login Account last login date
 * @param logout Account last logout date
 */
void Account::Set::date(DateTime created, DateTime login, DateTime logout) {
    account.date.created = created;
    account.date.last.login = login;
    account.date.last.logout = logout;
}

/**
 * @brief Get account id
 *
 * @return std::string Account id
 */
std::string Account::Get::id() {
    return account.id;
}

/**
 * @brief Get account name
 *
 * @param which Name type {first, middle, last, user}
 * @return std::string Selected account name
 */
std::string Account::Get::name(std::string which) {
    switch (which[0]) {
        case 'f':
            return account.name.first;
        case 'm':
            return account.name.middle;
        case 'l':
            return account.name.last;
        case 'u':
            return account.name.user;
        default:
            std::cerr << "Invalid name type" << std::endl;
            return "";
    }
}

/**
 * @brief Get account cvc
 *
 * @return int Account cvc
 */
std::string Account::Get::cvc() {
    return account.cvc;
}

/**
 * @brief Get account pin
 *
 * @return std::string Account pin
 */
std::string Account::Get::pin() {
    return account.pin;
}

/**
 * @brief Get account expiry
 *
 * @return std::int Account expiry {month, year}
 */
std::vector<int> Account::Get::expiry() {
    return {account.expiry.month, account.expiry.year};
}

/**
 * @brief Get account balance
 *
 * @return double Account balance
 */
double Account::Get::balance() {
    return account.balance.loan + account.balance.savings;
}

/**
 * @brief Get account date
 *
 * @return std::string Account date {created, last.login, last.logout}
 */
std::array<DateTime, 3> Account::Get::date() {
    return {account.date.created, account.date.last.login, account.date.last.logout};
}