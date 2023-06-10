#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Database handler
 *
 */
class Database {
   private:
    std::string filename;
    sqlite3* db;

   public:
    Database(std::string filename);
    int initDB();
    void closeDB();
    void create();
    void insert(Account account);
    void update(Account account);
    void remove(Account account);
    void select(Account account);
};

/**
 * @brief Account read and write structure
 *
 */
class Account {
   private:
    std::string id;
    bool create;
    struct Name {
        std::string first;
        std::string middle;
        std::string last;
        std::string user;
    } name;
    int cvc;
    std::string pin;
    std::string expiry;
    struct Balance {
        double loan;
        double savings;
    } balance;
    struct Date {
        std::string created;
        struct Last {
            std::string login;
            std::string logout;
        } last;
    } date;

    class Set {
       private:
        Account& account;

       public:
        Set(const Account& account);
        void id(std::string id);
        void name(std::string first, std::string middle, std::string last);
        void cvc(int cvc);
        void pin(std::string pin);
        void expiry(std::string expiry);
        void balance(double loan, double savings);
        void date(std::string created, std::string login, std::string logout);
    };
    class Get {
       private:
        Account& account;

       public:
        Get(const Account& account);
        std::string id();
        std::string name();
        int cvc();
        std::string pin();
        std::string expiry();
        double balance();
        std::string date();
    };

   public:
    Account(bool);
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
};

#endif  // DATABASE_H