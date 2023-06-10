#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include "../database.h"

class Handler {
   private:
    sqlite3* db;

    class HandAccount {
       private:
        Handler& handler;

       public:
        HandAccount(const Handler& handler);
        void create(Account& account, Name name, std::string pin);
        void edit();
        void get();
    };

    class History {
       private:
        Handler& handler;

       public:
        History(const Handler& handler);
        void create();
        void get();
    };

    class Loan {
       private:
        Handler& handler;

       public:
        Loan(const Handler& handler);
        void create();
        void edit();
        void get();
    };

   public:
    Handler();
    HandAccount account;
    History history;
    Loan loan;
    void setDB(sqlite3* db);

} handler;

#endif  // DB_HANDLER_H