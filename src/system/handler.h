#ifndef HANDLER_H
#define HANDLER_H

#include <sqlite3.h>
#include <sys/time.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "database.h"

//-------------------- Utility --------------------//
void pause(std::string message);
int confirm(std::string message);
void clear();

//-------------------- Schema --------------------//

/**
 * @brief Date and time structure
 *
 */
struct DateTime {
    int month;
    int day;
    int year;
    int hour;
    int minute;
    int second;
    int millisecond;
    std::string timezone;
    std::string toString(std::string which) const;
    DateTime fromString(std::string datetimezone);
    time_t toTime() const;
    double compare(DateTime time2) const;
};

/**
 * @brief Date and time structure
 *
 */
struct Name {
    std::string first;
    std::string middle;
    std::string last;
    std::string user;
};

//-------------------- Generator --------------------//

class Generator {
   private:
    int seed;
    int UTC = 0;
    Database& database;

   public:
    Generator(Database& database, int UTC);
    void randomizeSeed();
    std::string id(bool withChars, int length);
    int expiryYear();
    std::string cvc();
    DateTime getDate();
};

//-------------------- Builder --------------------//

/**
 * @brief History read and write structure
 *
 */
struct History {
    std::string log_id;  // History ID
    std::string id;
    std::string to_id;  // "transfer"
    DateTime date;
    std::string type;  // "deposit", "withdraw", "loan", "pay", "transfer", "login", "logout", "create"
    double amount;
    double balance;
    std::string merchant;
};

/**
 * @brief Account read and write structure
 *
 */
struct Account {
    std::string id;
    bool create;
    Name name;
    std::string cvc;
    std::string pin;
    struct Expiry {
        int month;
        int year;
    } expiry;
    struct Balance {
        double loan;
        double savings;
    } balance;
    double salary;
    struct Date {
        DateTime created;
        struct Last {
            DateTime login;
            DateTime logout;
        } last;
    } date;
};

/**
 * @brief Loan read and write structure
 *
 */
struct Loan {
    std::string reference;
    std::string id;
    std::string type;  // "create", "pay", "strike"
    double amount;
    double payed;
    int interest;
    int months;
    int months_left;
    int strikes;
    DateTime date;
};

//-------------------- Handler --------------------//

class Handler {
   private:
    Database& database;
    Generator generate;
    int UTC = 0;

    class HandAccount {
       private:
        Handler& handler;

       public:
        HandAccount(const Handler& thisHandler);
        int create(struct Account& account, Name name, std::string pin);
        int edit(struct Account& account);
        int login(struct Account& account, std::string id, std::string pin);
        int logout(struct Account& account);
        int update(struct Account& account, std::string id);
        int remove(std::string id);
    };

    class HandTransaction {
       private:
        Handler& handler;

       public:
        HandTransaction(const Handler& thisHandler);
        int deposit(struct Account& account, double amount, std::string merchant);
        int withdraw(struct Account& account, double amount, std::string merchant);
        int transfer(struct Account& account, std::string to_id, double amount, std::string merchant);
    };

    class HandHistory {
       private:
        Handler& handler;

       public:
        HandHistory(const Handler& thisHandler);
        int create(History& history, std::string id, std::string to_id, std::string type, double amount, double balance, std::string merchant);
        int get(History& history, std::string id, std::string type, std::string merchant);
    };

    class HandLoan {
       private:
        Handler& handler;

       public:
        HandLoan(const Handler& thisHandler);
        int create(struct Loan& loan, struct Account& account);
        std::vector<std::vector<int>> calculateLoanOptions(struct Loan& loan, struct Account& account, double strikePenalty, double maxLoanFactor, double minSalary, int minMembershipDays, int maxOptions);
        std::vector<std::vector<double>> getOptions(double amount);
        double calculateTotalAmount(double amount, double interestRate, int months);
        int pay(struct Loan& loan, struct Account& account, double amount);
        int current(struct Loan& loans, std::string id);
        int strike(struct Loan& loan, struct Account& account);
    };

   public:
    Handler(Database& database, int UTC);
    HandAccount account;
    HandTransaction transact;
    HandHistory history;
    HandLoan loan;
};

#endif  // HANDLER_H