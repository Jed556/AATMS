#include "../database.h"

/**
 * @brief Construct new Account object
 *
 */
Account::Account(bool create) {
    this->create = create;
    Set set(*this);
    Get get(*this);
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
void Account::Set::name(std::string first, std::string middle, std::string last) {
    account.name.first = first;
    account.name.middle = middle;
    account.name.last = last;
}

/**
 * @brief Set account cvc
 * 
 * @param cvc Account cvc
 */
void Account::Set::cvc(int cvc) {
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
void Account::Set::expiry(std::string expiry) {
    account.expiry = expiry;
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
void Account::Set::date(std::string created, std::string login, std::string logout) {
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
 * @return std::string Account name
 */
std::string Account::Get::name() {
    return account.name.first + " " + account.name.middle + " " + account.name.last;
}

/**
 * @brief Get account cvc
 * 
 * @return int Account cvc
 */
int Account::Get::cvc() {
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
 * @return std::string Account expiry
 */
std::string Account::Get::expiry() {
    return account.expiry;
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
 * @return std::string Account date
 */
std::string Account::Get::date() {
    return account.date.created + " " + account.date.last.login + " " + account.date.last.logout;
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