#ifndef HANDLER_H
#define HANDLER_H

#include <sqlite3.h>
#include <sys/time.h>
#include "database.h"

#include <algorithm>
#include <array>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

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
    std::string toString() const;
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

   public:
    void randomizeSeed();
    std::string id();
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
    double amount;
    std::string type;  // "deposit", "withdraw", "loan", "pay", "transfer", "login", "logout", "create"
    std::string merchant;
    DateTime date;
};

/**
 * @brief Account read and write structure
 *
 */
struct Account {
    std::string id;
    bool create;
    struct Name {
        std::string first;
        std::string middle;
        std::string last;
        std::string user;
    } name;
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
    double amount;
    double amount_payed;
    int months;
    int months_left;
    std::vector<History> history;
};

//-------------------- Handler --------------------//

class Handler {
   private:
    Database& database;
    Generator* generate;

    class HandAccount {
       private:
        Handler& thisHandler;

       public:
        HandAccount(const Handler& thisHandler);
        void create(Account& account, Name name, std::string pin);
        void edit();
        void get();
    };

    class HandHistory {
       private:
        Handler& thisHandler;

       public:
        HandHistory(const Handler& thisHandler);
        void create();
        void get();
    };

    class HandLoan {
       private:
        Handler& thisHandler;

       public:
        HandLoan(const Handler& thisHandler);
        void create();
        void edit();
        void get();
    };

   public:
    Handler(Database& database);
    HandAccount account;
    HandHistory history;
    HandLoan loan;
};

#endif  // HANDLER_H