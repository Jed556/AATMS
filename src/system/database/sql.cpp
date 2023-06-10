#include "../database.h"

Database::Database(std::string path) {
    this->path = path;
}

std::string Database::constructString(std::string statement, std::string table, std::vector<std::string> column, bool hasValue, std::vector<std::string> value) {
    std::string sql = statement + " " + table + " (";

    for (int i = 0; i < column.size(); i++) {
        sql += column[i];

        if (i != column.size() - 1) {
            sql += ", ";
        }
    }

    if (hasValue) {
        sql += ") VALUES (";

        for (int i = 0; i < value.size(); i++) {
            sql += "'" + value[i] + "'";

            if (i != value.size() - 1) {
                sql += ", ";
            }
        }
    }

    sql += ");";

    return sql;
}

int Database::openDB() {
    int rc = sqlite3_open_v2(path.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    if (rc) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }
    return 0;
}

void Database::closeDB() {
    sqlite3_close(db);
}

sqlite3* Database::getDB() {
    return db;
}

void Database::create(std::string table, std::vector<std::string> column) {
    char* errMsg;
    int rc;

    std::string sql = constructString("CREATE TABLE IF NOT EXISTS", table, column, false, {});

    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table created successfully." << std::endl;
    }
}

void Database::insert(std::string table, std::vector<std::string> column, std::vector<std::string> value) {
    std::string sql = constructString("INSERT INTO", table, column, true, value);

    char* errMsg;
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Error inserting data: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Data inserted successfully." << std::endl;
    }
}