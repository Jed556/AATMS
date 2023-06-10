#include "../database.h"

int Database::initDB() {
    sqlite3* db;
    int rc = sqlite3_open_v2("../database/bank.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    if (rc) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }
}

void Database::closeDB() {
    sqlite3_close(db);
}