#include "system/AATMS.h"

int WinMain(int argc, char const* argv[]) {
    // Initialize
    Account account;
    Database database("../database/database.db");
    Handler handler(database, +8);
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
         "TEXT NOT NULL",
         "TEXT NOT NULL",
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

    int choice = 0;
    while (choice != -1) {
        std::cout << "----- Welcome to AATMS -----" << std::endl;
        std::cout << "Enter 1 to login or 2 to create account: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Login
                std::string username, pin;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter PIN: ";
                std::cin >> pin;

                if (true) {  // handler.account.login(username, pin)
                    std::cout << "Login successful!" << std::endl;
                    // Show account options after successful login
                    int accountOption = -1;
                    while (accountOption != 6) {
                        std::cout << "\nEnter 1 to check balance, 2 to deposit, 3 to withdraw, 4 to transfer, 5 for loan, or 6 to logout: ";
                        std::cin >> accountOption;

                        std::string transferUserId;
                        switch (accountOption) {
                            case 1:
                                // Check balance
                                std::cout << "Balance: $X.XX" << std::endl;  // Placeholder
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
                } else {
                    std::cout << "Invalid username or PIN. Please try again." << std::endl;
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
                std::cout << "Enter PIN: ";
                std::cin >> pin;

                Name name = {firstName, middleName, lastName, userName};
                handler.account.create(account, name, pin);
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

        system("cls");
    }

    database.closeDB();

    return 0;
}