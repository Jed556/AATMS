#include "system/AATMS.h"

std::string databasePath = "../database/database.db";

int Init(Database& database) {
    database.openDB();

    database.create(
        "accounts",
        {"id", "first", "middle", "last", "user", "cvc", "pin", "month", "year", "loan", "savings", "created"},
        {"TEXT PRIMARY KEY",
         "TEXT NOT NULL",
         "TEXT",
         "TEXT NOT NULL",
         "TEXT NOT NULL",
         "TEXT NOT NULL",
         "TEXT NOT NULL",
         "INTEGER NOT NULL",
         "INTEGER NOT NULL",
         "REAL NOT NULL",
         "REAL NOT NULL",
         "TEXT NOT NULL"});

    database.create(
        "history",
        {"log_id", "id", "to_id", "date", "time", "type", "amount", "balance", "description", "merchant"},
        {"TEXT PRIMARY KEY",
         "TEXT NOT NULL",
         "TEXT",
         "TEXT NOT NULL",
         "TEXT NOT NULL",
         "TEXT NOT NULL",
         "REAL NOT NULL",
         "REAL NOT NULL",
         "TEXT NOT NULL",
         "TEXT NOT NULL"});
    return 0;
}

int loop(Handler& handler, Account& account) {
    int choice = 0;
    while (choice != -1) {
        std::cout << "----- Welcome to AATMS -----" << std::endl;
        std::cout << "Enter 1 to login or 2 to create account: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Login
                std::string id, pin;
                std::cout << "Enter your id: ";
                std::cin >> id;
                std::cout << "Enter PIN: ";
                std::cin >> pin;

                if (handler.account.login(account, id, pin)) {
                    int accountOption = -1;
                    while (accountOption != 6) {
                        std::cout << "\n----- Account Options -----   ----- " << account.name.user << " -----   Balance: " << account.balance.savings << " -----" << std::endl;
                        std::cout << "\nEnter 1 to check balance, 2 to deposit, 3 to withdraw, 4 to transfer, 5 for loan, or 6 to logout: ";
                        std::cin >> accountOption;

                        std::string transferUserId;
                        switch (accountOption) {
                            case 1:
                                // Check balance
                                std::cout << "Balance: $" << account.balance.savings << std::endl;  // Placeholder
                                break;
                            case 2:
                                // Deposit
                                double depositAmount;
                                std::cout << "Enter amount to deposit: ";
                                std::cin >> depositAmount;
                                std::cout << "Deposit amount: $" << depositAmount << std::endl;  // Placeholder
                                break;
                            case 3:
                                // Withdraw
                                double withdrawAmount;
                                std::cout << "Enter amount to withdraw: ";
                                std::cin >> withdrawAmount;
                                std::cout << "Withdrawal amount: $" << withdrawAmount << std::endl;  // Placeholder
                                break;
                            case 4:
                                // Transfer
                                double transferAmount;
                                std::cout << "Enter user ID to transfer to: ";
                                std::cin >> transferUserId;
                                std::cout << "Enter amount to transfer: ";
                                std::cin >> transferAmount;
                                std::cout << "Transfer amount: $" << transferAmount << " to user ID: " << transferUserId << std::endl;  // Placeholder
                                break;
                            case 5:
                                // Loan
                                double loanAmount;
                                std::cout << "Enter amount to loan: ";
                                std::cin >> loanAmount;
                                std::cout << "Loan amount: $" << loanAmount << std::endl;  // Placeholder
                                break;
                            case 6:
                                // Logout
                                std::cout << "Logging out..." << std::endl;
                                choice = 0;
                                break;
                            default:
                                std::cout << "Invalid choice. Please try again." << std::endl;
                                break;
                        }
                    }
                }
                break;
            }
            case 2: {
                // Create account
                std::string firstName, middleName, lastName, userName, pin;
                std::cout << "Enter first name: ";
                std::cin >> firstName;
                std::cout << "Enter middle name: ";
                std::cin >> middleName;
                std::cout << "Enter last name: ";
                std::cin >> lastName;
                std::cout << "Enter username: ";
                std::cin >> userName;

                while (true) {
                    std::cout << "Enter PIN: ";
                    std::cin >> pin;
                    if (pin.length() != 4) {
                        std::cout << "Invalid PIN length. Please try again." << std::endl;
                        continue;
                    }

                    int valid = true;
                    for (char c : pin) {
                        if (c < '0' || c > '9') {
                            valid = false;
                            break;
                        }
                        std::cout << c << std::endl;
                    }

                    if (!valid) {
                        std::cout << "Invalid PIN. Please enter 4 valid integers (0-9)." << std::endl;
                        continue;
                    }

                    break;
                }

                Name name = {firstName, middleName, lastName, userName};
                int res = handler.account.create(account, name, pin);
                std::cout << "Account created successfully!" << std::endl;
                break;
            }
            case -1: {
                // Exit
                std::cout << "Exiting..." << std::endl;
                return 0;
            }
            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }

        clear();
    }
    return 0;
}

int WinMain(int argc, char const* argv[]) {
    // Initialize
    Account account;
    Database database(databasePath);
    Handler handler(database, +8);
    Init(database);

    loop(handler, account);

    database.closeDB();

    return 0;
}