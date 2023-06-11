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
        clear();
        std::cout << "----- Welcome to AATMS -----" << std::endl;
        std::cout << "\nOPTIONS:   [1] Login   [2] Create Account";
        std::cout << "\n>> ";
        std::cin >> choice;
        std::cout << std::endl;

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
                        clear();
                        std::cout << "\n----- Account Options -----   ----- " << account.name.user
                                  << " -----   ----- Balance: " << account.balance.savings << " -----" << std::endl;
                        std::cout << "\nOPTIONS:   [1] Check Balance   [2] Deposit   [3] Withdraw   [4] Transfer   [5] Loan   [6] Logout";
                        std::cout << "\n>> ";
                        std::cin >> accountOption;

                        std::cout << std::endl;
                        std::string transferUserId;
                        switch (accountOption) {
                            case 1:
                                // Check balance
                                std::cout << "Balance: $" << account.balance.savings << std::endl;  // Placeholder
                                std::cout << std::endl;
                                pause("Press Enter to go back...");
                                break;
                            case 2:
                                // Deposit
                                double depositAmount;
                                std::cout << "Enter amount to deposit: ";
                                std::cin >> depositAmount;
                                std::cout << "Deposit amount: $" << depositAmount << std::endl;  // Placeholder
                                std::cout << std::endl;
                                pause("Press Enter to go back...");
                                break;
                            case 3:
                                // Withdraw
                                double withdrawAmount;
                                std::cout << "Enter amount to withdraw: ";
                                std::cin >> withdrawAmount;
                                std::cout << "Withdrawal amount: $" << withdrawAmount << std::endl;  // Placeholder
                                std::cout << std::endl;
                                pause("Press Enter to go back...");
                                break;
                            case 4:
                                // Transfer
                                double transferAmount;
                                std::cout << "Enter user ID to transfer to: ";
                                std::cin >> transferUserId;
                                std::cout << "Enter amount to transfer: ";
                                std::cin >> transferAmount;
                                std::cout << "Transfer amount: $" << transferAmount << " to user ID: " << transferUserId << std::endl;  // Placeholder
                                std::cout << std::endl;
                                pause("Press Enter to go back...");
                                break;
                            case 5:
                                // Loan
                                double loanAmount;
                                std::cout << "Enter amount to loan: ";
                                std::cin >> loanAmount;
                                std::cout << "Loan amount: $" << loanAmount << std::endl;  // Placeholder
                                std::cout << std::endl;
                                pause("Press Enter to go back...");
                                break;
                            case 6:
                                // Logout
                                std::cout << "Logging out..." << std::endl;
                                choice = 0;
                                std::cout << std::endl;
                                pause("Logged out. Press Enter to continue...");
                                break;
                            default:
                                pause("Invalid choice. Press Enter to try again...");
                                break;
                        }
                    }
                }
                break;
            }
            case 2: {
                // Create account
                clear();
                std::cout << "----- Welcome to AATMS -----   ----- Account Creation -----" << std::endl;

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
                    int valid = true;
                    clear();
                    std::cout << "----- Welcome to AATMS -----   ----- Account Creation -----" << std::endl;
                    std::cout << "Enter first name: " << firstName << std::endl;
                    std::cout << "Enter middle name: " << middleName << std::endl;
                    std::cout << "Enter last name: " << lastName << std::endl;
                    std::cout << "Enter username: " << userName << std::endl;

                    std::cout << "Enter PIN: ";
                    std::cin >> pin;
                    if (pin.length() != 4) {
                        std::cout << "Invalid PIN length. Please try again." << std::endl;
                        valid = false;
                    }

                    for (char c : pin) {
                        if (c < '0' || c > '9') {
                            valid = false;
                            std::cout << "Invalid PIN. Please enter 4 valid integers (0-9)." << std::endl;
                            break;
                        }
                    }

                    if (!valid) continue;
                    break;
                }

                Name name = {firstName, middleName, lastName, userName};
                handler.account.create(account, name, pin);
                pause("Account created successfully! Press Enter to continue...");

                clear();
                std::cout << "----- Welcome to AATMS " << account.name.user << " -----" << std::endl;
                std::cout << std::endl;
                std::cout << "Your user ID is: " << account.id << std::endl;
                std::cout << "Your CVC is: " << account.cvc << std::endl;
                std::cout << "Your Expiration Date is: " << (account.expiry.month < 10 ? "0" : "") << account.expiry.month << "/" << account.expiry.year << std::endl;
                std::cout << std::endl;
                std::cout << "Please keep this information safe." << std::endl;
                pause("Press Enter to continue...");
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