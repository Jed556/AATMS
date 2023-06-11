#include "../database.h"

Database::Database(std::string path) {
    this->path = path;
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

/**
 * @brief Callbank function for database interface
 * 
 * @return int 
 */
static int callback(void* data, int argc, char** argv, char** azColName) {
    // Cast the data pointer to the vector of RowData
    std::vector<RowData>* rows = static_cast<std::vector<RowData>*>(data);


    // Push each column of the current row
    RowData rowData;
    for (int i = 0; i < argc; i++) {
        rowData.columnValues.push_back(argv[i]);
    }

    // Add the current row to the vector of rows
    rows->push_back(rowData);

    return 0;
}

/**
 * @brief Connect to the database
 * 
 * @return int 
 */
int Database::openDB() {
    int rc = sqlite3_open_v2(path.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    if (rc) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }
    return 0;
}

/**
 * @brief Disconnect from the database
 * 
 */
void Database::closeDB() {
    sqlite3_close(db);
}

/**
 * @brief Get the database object
 * 
 * @return sqlite3* 
 */
sqlite3* Database::getDB() {
    return db;
}

/**
 * @brief Execute a SQL statement
 * 
 * @param sql The SQL statement to execute
 * @param type The type of SQL statement
 * @return std::vector<RowData> The retrieved data
 */
std::vector<RowData> Database::execute(std::string sql, std::string type) {
    std::vector<RowData> rows;  // Vector to store the retrieved data

    char* errMsg;
    int rc = sqlite3_exec(db, sql.c_str(), callback, &rows, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "[ERROR] " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return rows;
    } else {
        // Process the retrieved data from the vector of rows
        // std::cout << "[SUCCESS] " << sql << std::endl << "[MATCH] ";
        // for (const auto& row : rows) {
        //     for (const auto& value : row.columnValues) {
        //         std::cout << value << " ";
        //     }
        //     std::cout << std::endl;
        // }
        return rows;
    }
}

/**
 * @brief Select data from the database
 * 
 * @param table The table to select from
 * @param columns The columns to select
 * @param condition Condition to filter data
 * @return std::vector<RowData> The retrieved data
 */
std::vector<RowData> Database::select(std::string table, std::vector<std::string> columns, std::string condition) {
    std::string sql = "SELECT ";
    for (int i = 0; i < columns.size(); i++) {
        sql += columns[i];
        if (i != columns.size() - 1) {
            sql += ", ";
        }
    }

    sql += " FROM " + table;

    if (!condition.empty()) {
        sql += " WHERE " + condition;
    }
    sql += ";";
    std::vector<RowData> rows = execute(sql, "select");
    return rows;
}

/**
 * @brief Create a table in the database
 * 
 * @param table The table to create
 * @param columns The columns to create
 * @param constraints The constraints to apply to the columns
 */
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

/**
 * @brief Insert data into a table in the database
 * 
 * @param table The table to insert into
 * @param column The columns to insert into
 * @param value The values to insert into the columns
 */
void Database::insert(std::string table, std::vector<std::string> column, std::vector<std::string> value) {
    std::string sql = constructString("INSERT INTO", table, column, value);
    execute(sql, "insert");
}

/**
 * @brief Update data in a table in the database
 * 
 * @param table The table to update
 * @param setColumns The columns to update
 * @param setValues The values to update the columns to
 * @param condition Condition to filter data
 */
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

/**
 * @brief Remove data from a table in the database
 * 
 * @param table The table to remove from
 * @param condition Condition to filter data
 */
void Database::remove(std::string table, std::string condition) {
    std::string sql = "DELETE FROM " + table;
    if (!condition.empty()) {
        sql += " WHERE " + condition;
    }
    sql += ";";
    execute(sql, "remove");
}