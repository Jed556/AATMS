#ifndef DB_SCHEMA_H
#define DB_SCHEMA_H

#include "../database.h"

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

/**
 * @brief Account read and write structure
 *
 */
class Account {
   private:
    Generator* generate;
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

    class Set {
       private:
        Account& account;

       public:
        Set(const Account& account);
        void id(std::string id);
        void name(std::string first, std::string middle, std::string last, std::string user);
        void cvc(std::string cvc);
        void pin(std::string pin);
        void expiry(int month, int year);
        void balance(double loan, double savings);
        void date(DateTime created, DateTime login, DateTime logout);
    };
    class Get {
       private:
        Account& account;

       public:
        Get(const Account& account);
        std::string id();
        std::string name(std::string which);
        std::string cvc();
        std::string pin();
        std::vector<int> expiry();
        double balance();
        std::array<DateTime, 3> date();
    };

   public:
    Account(bool);
    Set set;
    Get get;
};

/**
 * @brief Loan read and write structure
 *
 */
class Loan {
   private:
    double amount;
    double amount_payed;
    int months;
    int months_left;
    std::vector<History> history;

    class Set {
       private:
        Loan& loan;

       public:
        Set(const Loan& loan);
        void amount(double amount);
        void amountPayed(double amount_payed);
        void months(int months);
        void monthsLeft(int months_left);
        void history(std::vector<History> history);
    };
    struct Get {
       private:
        Loan& loan;

       public:
        Get(const Loan& loan);
        double amount();
        double amountPayed();
        int months();
        int monthsLeft();
        std::vector<History> history();
    };

   public:
    Loan();
    Set set;
    Get get;
};

/**
 * @brief History read and write structure
 *
 */
class History {
   private:
    double amount;
    std::string type;  // "deposit", "withdraw", "loan", "pay", "transfer", "login", "logout", "create"
    std::string merchant;
    std::string date;

    struct Set {
       private:
        History& history;

       public:
        Set(const History& history);
        void amount(double amount);
        void type(std::string type);
        void merchant(std::string merchant);
        void date(std::string date);
    };
    struct Get {
       private:
        History& history;

       public:
        Get(const History& history);
        double amount();
        std::string type();
        std::string merchant();
        std::string date();
    };

   public:
    History();
    Set set;
    Get get;
};

#endif  // DB_SCHEMA_H