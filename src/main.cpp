#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sqlite3.h>
#include <string>

// Function to generate a random 16-character account ID
std::string generateAccountID() {
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int length = 16;
    std::string accountID;
    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % chars.length();
        accountID += chars[randomIndex];
    }
    return accountID;
}

// Function to generate a random expiration month (01-12)
std::string generateExpirationMonth() {
    int randomMonth = rand() % 12 + 1;
    return (randomMonth < 10) ? "0" + std::to_string(randomMonth) : std::to_string(randomMonth);
}

// Function to generate a random expiration year (2023-2033)
std::string generateExpirationYear() {
    int randomYear = rand() % 11 + 2023;
    return std::to_string(randomYear);
}

// Function to generate a random 3-character CVC
std::string generateCVC() {
    const std::string chars = "0123456789";
    const int length = 3;
    std::string cvc;
    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % chars.length();
        cvc += chars[randomIndex];
    }
    return cvc;
}

// Function to create a new account
void createAccount(sqlite3* db, const std::string& firstName, const std::string& lastName, const std::string& pin) {
    char* errMsg;
    int rc;

    // Generate random values for account ID, expiration month, year, and CVC
    std::string accountID = generateAccountID();
    std::string expirationMonth = generateExpirationMonth();
    std::string expirationYear = generateExpirationYear();
    std::string cvc = generateCVC();

    // Prepare the nested loan history document
    std::string loanHistory = "[{\"amount_payed\":\"100\",\"date\":\"2023-06-09\"}]";

    // Prepare the nested loans array
    std::string loansArray = "[{\"balance\":5000,\"months\":12,\"months_left\":6,\"history\":" + loanHistory + "}]";

    // Prepare the SQL statement
    std::string sql = "INSERT INTO accounts (id, first, last, month, year, cvc, loans, balance, pin) VALUES ('" + accountID + "', '" + firstName + "', '" + lastName + "', '" + expirationMonth + "', '" + expirationYear + "', '" + cvc + "', '" + loansArray + "', 0.0, '" + pin + "');";

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Error creating account: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Account created successfully." << std::endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    sqlite3* db;
    int rc = sqlite3_open_v2("../database/bank.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    if (rc) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    std::string firstName, lastName, pin;
    std::cout << "Enter first name: ";
    std::cin >> firstName;
    std::cout << "Enter last name: ";
    std::cin >> lastName;
    std::cout << "Enter PIN: ";
    std::cin >> pin;

    createAccount(db, firstName, lastName, pin);

    sqlite3_close(db);
    system("pause");

    return 0;
}