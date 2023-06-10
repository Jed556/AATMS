#ifndef DB_SQL_H
#define DB_SQL_H

#include "../database.h"

/**
 * @brief Database handler
 *
 */
class Database {
   private:
    std::string path;
    sqlite3* db;

    std::string constructString(std::string statement, std::string table, std::vector<std::string> column, bool hasValue, std::vector<std::string> value);

   public:
    Database(std::string path);
    int openDB();
    void closeDB();
    sqlite3* getDB();
    void create();
    void insert(Account account, std::string table, std::vector<std::string> column, std::vector<std::string> value);
    void update(Account account);
    void remove(Account account);
    void select(Account account);
    void execute(std::string sql);
};

#endif  // DB_SQL_H