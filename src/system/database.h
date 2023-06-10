#ifndef DB_SQL_H
#define DB_SQL_H

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
    std::string path;
    sqlite3* db;

    std::string constructString(std::string statement, std::string table, std::vector<std::string> column, bool hasValue, std::vector<std::string> value);

   public:
    Database(std::string path);
    int openDB();
    void closeDB();
    sqlite3* getDB();
    void create(std::string table, std::vector<std::string> column);
    void insert(std::string table, std::vector<std::string> column, std::vector<std::string> value);
    void update();
    void remove();
    void select();
    void execute(std::string sql);
};

#endif  // DB_SQL_H