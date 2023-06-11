#ifndef DB_SQL_H
#define DB_SQL_H

#include <sqlite3.h>

#include <iostream>
#include <string>
#include <vector>

struct RowData {
    std::vector<std::string> columnValues;
};

static int callback(void* data, int argc, char** argv, char** azColName);

/**
 * @brief Database handler
 *
 */
class Database {
   private:
    std::string path;
    sqlite3* db;

    std::string constructString(std::string statement, std::string table, std::vector<std::string> column, std::vector<std::string> value);

   public:
    Database(std::string path);
    int openDB();
    void closeDB();
    sqlite3* getDB();
    std::vector<RowData> execute(std::string sql, std::string type);
    std::vector<RowData> select(std::string table, std::vector<std::string> columns, std::string condition);
    void create(std::string table, std::vector<std::string> columns, std::vector<std::string> constraints);
    void insert(std::string table, std::vector<std::string> column, std::vector<std::string> value);
    void update(std::string table, std::vector<std::string> column, std::vector<std::string> value, std::string condition);
    void remove(std::string table, std::string condition);
};

#endif  // DB_SQL_H