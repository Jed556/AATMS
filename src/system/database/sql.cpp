#include "../database.h"

Database::Database(std::string path) {
    this->path = path;
}

int Database::execute(std::string sql, std::string type) {
    char* errMsg;
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "[ERROR] " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 1;
    } else {
        std::cout << "[SUCCESS] " << sql << std::endl;
        return 0;
    }
}

std::string Database::select(std::string table, std::string columns, std::string condition) {
    std::string sql = "SELECT " + columns + " FROM " + table;
    if (!condition.empty()) {
        sql += " WHERE " + condition;
    }
    sql += ";";
    return sql;
}

std::string Database::constructString(std::string statement, std::string table, std::vector<std::string> column, std::vector<std::string> value) {
    std::string sql = statement + " " + table + " (";

    // Retrieve column information from the database
    std::string pragmaSql = "PRAGMA table_info(" + table + ");";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, pragmaSql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "[ERROR] Failed to retrieve column information: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    std::vector<std::string> columnTypes;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string columnName = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string columnType = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        columnTypes.push_back(columnType);
    }
    sqlite3_finalize(stmt);

    for (int i = 0; i < column.size(); i++) {
        sql += column[i];

        if (i != column.size() - 1) {
            sql += ", ";
        }
    }

    if (!value.empty()) {
        sql += ") VALUES (";

        for (int i = 0; i < value.size(); i++) {
            // Check if the column type is INTEGER or DOUBLE
            if (columnTypes[i].find("INT") != std::string::npos || columnTypes[i].find("DOUBLE") != std::string::npos) {
                sql += value[i];
            } else {
                sql += "'" + value[i] + "'";
            }

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

void Database::create(std::string table, std::vector<std::string> columns, std::vector<std::string> constraints) {
    for (int i = 0; i < columns.size(); i++) {
        if (!constraints.empty() && i < constraints.size()) {
            columns[i] += " " + constraints[i];
        } else {
            columns[i] += " TEXT";
        }
    }
    std::string sql = constructString("CREATE TABLE IF NOT EXISTS", table, columns, {});
    execute(sql, "create");
}

void Database::insert(std::string table, std::vector<std::string> column, std::vector<std::string> value) {
    std::string sql = constructString("INSERT INTO", table, column, value);
    execute(sql, "insert");
}

void Database::update(std::string table, std::vector<std::string> setColumns, std::vector<std::string> setValues, std::string condition) {
    std::string setClause;
    if (setColumns.size() == setValues.size()) {
        for (size_t i = 0; i < setColumns.size(); ++i) {
            setClause += setColumns[i] + " = '" + setValues[i] + "'";
            if (i != setColumns.size() - 1) {
                setClause += ", ";
            }
        }
    }

    std::string sql = "UPDATE " + table + " SET " + setClause;
    if (!condition.empty()) {
        sql += " WHERE " + condition;
    }
    sql += ";";

    execute(sql, "update");
}

void Database::remove(std::string table, std::string condition) {
    std::string sql = "DELETE FROM " + table;
    if (!condition.empty()) {
        sql += " WHERE " + condition;
    }
    sql += ";";
    execute(sql, "remove");
}