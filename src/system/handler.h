#ifndef HANDLER_H
#define HANDLER_H

#include <sqlite3.h>
#include <sys/time.h>

#include <algorithm>
#include <array>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "database.h"

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

   public:
    Generator(int UTC);
    void randomizeSeed();
    std::string id();
    int expiryYear();
    std::string cvc();
    DateTime getDate(int UTC);
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
    std::string loan_id;
    std::string id;
    std::string type;  // "create", "pay", "strike"
    double amount;
    double payed;
    int interest;
    int months;
    int months_left;
    int strikes;
    std::vector<History> history;
};

//-------------------- Handler --------------------//

class Handler {
   private:
    Database& database;
    Generator* generate;
    int UTC = 0;

    class HandAccount {
       private:
        Handler& handler;

       public:
        HandAccount(const Handler& thisHandler);
        int create(Account& account, Name name, std::string pin);
        int edit(Account& account, Name name, std::string pin);
        int get();
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
        int create(Loan& loan, std::string loan_id, std::string id, std::string type, double amount, int interest, int months);
        int get(Loan& loan, std::string loan_id, std::string id, std::string type, std::string merchant, std::string date);
        int pay(Loan& loan, double amount);
        int strike(Loan& loan, History& history);
    };

   public:
    Handler(Database& database, int UTC);
    HandAccount account;
    HandHistory history;
    HandLoan loan;
};

#endif  // HANDLER_H