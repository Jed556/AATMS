#include "system/AATMS.h"

std::string databasePath = "../database/database.db";

int Init(Database& database) {
    database.openDB();

    database.create(
        "accounts",
        {"id", "first", "middle", "last",
         "user", "cvc", "pin", "month",
         "year", "loan", "savings", "created"},
        {"TEXT PRIMARY KEY", "TEXT NOT NULL", "TEXT", "TEXT NOT NULL",
         "TEXT NOT NULL", "TEXT NOT NULL", "TEXT NOT NULL", "INTEGER NOT NULL",
         "INTEGER NOT NULL", "REAL NOT NULL", "REAL NOT NULL", "TEXT NOT NULL"});

    database.create(
        "history",
        {"log_id", "id", "to_id", "date",
         "time", "type", "amount", "balance",
         "description", "merchant"},
        {"TEXT PRIMARY KEY", "TEXT NOT NULL", "TEXT", "TEXT NOT NULL",
         "TEXT NOT NULL", "TEXT NOT NULL", "REAL NOT NULL", "REAL NOT NULL",
         "TEXT NOT NULL", "TEXT NOT NULL"});

    database.create(
        "loans",
        {"reference", "id", "type", "amount",
         "payed", "interest", "months", "months_left",
         "strikes", "date"},
        {"TEXT PRIMARY KEY", "TEXT NOT NULL", "TEXT NOT NULL", "REAL NOT NULL",
         "REAL NOT NULL", "INTEGER NOT NULL", "INTEGER NOT NULL", "INTEGER NOT NULL",
         "INTEGER NOT NULL", "TEXT NOT NULL"});

    return 0;
}

int Create(Account& account, Handler& handler) {
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
            valid = false;
            pause("Invalid PIN length. Press Enter to try again...");
            continue;
        }

        for (int i = 0; i < pin.length(); i++) {
            if (pin[i] < '0' || pin[i] > '9') {
                valid = false;
                std::cout << "Invalid PIN. Please enter 4 valid integers (0-9)." << std::endl;
                pause("Press Enter to try again...");
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

    return 0;
}

int Login(Account& account, Handler& handler) {
    std::string id, pin;
    std::cout << "Enter your id: ";
    std::cin >> id;
    std::cout << "Enter PIN: ";
    std::cin >> pin;
    int err = handler.account.login(account, id, pin);

    if (err) {
        std::cout << "Login failed!";
        if (err == 1)
            std::cout << "Account not found!" << std::endl;
        else if (err == 2)
            std::cout << "Incorrect PIN!" << std::endl;

        std::cout << std::endl;
        pause("Press Enter to go back...");
    } else {
        std::cout << "Login successful!" << std::endl;
        std::cout << std::endl;
        std::cout << "Logged in as " << account.name.user << std::endl;
        std::cout << "Account ID: " << account.id << std::endl;
        std::cout << "Name: " << account.name.first << " " << account.name.middle << " " << account.name.last << std::endl;
        // std::cout << "Name: " << account.name.first << " " << account.name.middle << " " << account.name.last << std::endl;
        // std::cout << "Username: " << account.name.user << std::endl;
        // std::cout << "CVC: " << account.cvc << std::endl;
        // std::cout << "PIN: " << account.pin << std::endl;
        // std::cout << "Expiry: " << account.expiry.month << "/" << account.expiry.year << std::endl;
        std::cout << "Loan Balance: " << account.balance.loan << std::endl;
        std::cout << "Savings Balance: " << account.balance.savings << std::endl;
        std::cout << "Created: " << account.date.created.toString("full") << std::endl;
        pause("\nPress enter to continue...");
    }
    return err;
}

void Deposit(Account& account, Handler& handler) {
    double depositAmount;
    std::cout << "Enter amount to deposit: ";
    std::cin >> depositAmount;
    std::cout << std::endl;

    if (!handler.transact.deposit(account, depositAmount, "AATMS")) {
        std::cout << "Deposited $" << depositAmount << std::endl;
    } else {
        std::cout << "Deposit failed! Invalid amount." << std::endl;
    }
    pause("Press Enter to go back...");
}

void Withdraw(Account& account, Handler& handler) {
    double withdrawAmount;
    std::cout << "Enter amount to withdraw: ";
    std::cin >> withdrawAmount;
    std::cout << std::endl;

    if (!handler.transact.withdraw(account, withdrawAmount, "AATMS")) {
        std::cout << "Withdrawn $" << withdrawAmount << std::endl;
    } else if (account.balance.savings < withdrawAmount) {
        std::cout << "Withdraw failed! Insufficient funds." << std::endl;
    } else {
        std::cout << "Withdraw failed! Invalid amount." << std::endl;
    }
    pause("Press Enter to go back...");
}

void Transfer(Account& account, Handler& handler, Database& database) {
    std::string transferUserId;
    double transferAmount;
    std::cout << "Enter user ID to transfer to: ";
    std::cin >> transferUserId;
    std::cout << "Enter amount to transfer: ";
    std::cin >> transferAmount;
    std::cout << "Transfer amount: $" << transferAmount << " to user ID: " << transferUserId << std::endl;  // Placeholder
    std::cout << std::endl;

    std::string transferNameUser;
    int err = handler.transact.transfer(account, transferUserId, transferAmount, "AATMS");
    if (!err) {
        std::string check = "id = '" + transferUserId + "'";
        transferNameUser = database.select("accounts", {"id", "user"}, check)[0].columnValues[1];
    }
    switch (err) {
        case 0:
            std::cout << "Successfully transferred $" << transferAmount << " to " << transferNameUser << std::endl;
            break;
        case 1:
            std::cout << "Transfer failed! Invalid amount." << std::endl;
            break;
        case 2:
            std::cout << "Transfer failed! Insufficient funds." << std::endl;
            break;
        case 3:
            std::cout << "Transfer failed! Can't transfer to the same account." << std::endl;
            break;
        case 4:
            std::cout << "Transfer failed! User doesn't exist." << std::endl;
            break;
    }
    pause("Press Enter to go back...");
}

void Loan(Account& account, Handler& handler) {
    struct Loan loan;
    int choice = 0;
    while (true) {
        clear();
        std::cout << "----- Loan Options -----   ----- " << account.name.user
                  << " -----   ----- Balance: $" << account.balance.savings << " -----" << std::endl;
        std::cout << "\nOPTIONS:   [1] Refresh   [2] Create   [3] Pay   [4] Back";

        int hasLoan = handler.loan.current(loan, account.id);
        if (loan.payed < loan.amount && hasLoan != 0) {
            std::cout << "\n\n";
            std::cout << "Active Loan:   $" << loan.payed << " / $" << loan.amount << " at " << loan.interest << "%"
                      << " for " << loan.months << " months";
            std::cout << std::endl;
        }
        std::cout << "\n>> ";
        std::cin >> choice;

        int plan;
        bool cancel = false;
        int err = 0;
        switch (choice) {
            case 1:
                handler.account.update(account, account.id);
                handler.loan.current(loan, account.id);
                break;
            case 2:
                hasLoan = handler.loan.current(loan, account.id);
                if (loan.payed < loan.amount && hasLoan != 0) {
                    std::cout << "You already have an active loan. Please pay it off before creating a new one." << std::endl;
                    pause("Press Enter to go back...");
                    break;
                }
                while (true) {
                    std::cout << "Enter amount to loan: ";
                    std::cin >> loan.amount;

                    std::cout << std::endl;
                    std::cout << "Plans ---------" << std::endl;
                    int numOptions = handler.loan.getOptions(loan.amount).size();
                    for (int i = 0; i < numOptions; i++) {
                        std::cout << "Option [" << i + 1 << "]: " << std::endl;
                        std::cout << "Total Amount: $" << handler.loan.getOptions(loan.amount)[i][0] << std::endl;
                        std::cout << "Months: " << handler.loan.getOptions(loan.amount)[i][1] << " months" << std::endl;
                        std::cout << "Interest Rate: " << handler.loan.getOptions(loan.amount)[i][2] << "%" << std::endl;
                        std::cout << std::endl;
                    }

                    std::cout << "[" << numOptions + 1 << "] Cancel" << std::endl;

                    std::cout << "\n>> ";
                    std::cin >> plan;
                    if (plan > numOptions + 1) {
                        pause("Invalid Plan Index. Press any key to retry...");
                        continue;
                    }
                    if (plan == numOptions + 1) {
                        cancel = true;
                        loan = {};
                    }

                    break;
                }

                if (cancel) {
                    std::cout << "Cancelled loan creation" << std::endl;
                    pause("Press Enter to go back...");
                    break;
                }

                --plan;
                loan.amount = handler.loan.getOptions(loan.amount)[plan][0];
                loan.months = handler.loan.getOptions(loan.amount)[plan][1];
                loan.interest = handler.loan.getOptions(loan.amount)[plan][2];

                std::cout << "Details -------" << std::endl;
                std::cout << "Total Amount: $" << loan.amount << std::endl;
                std::cout << "Monthly Payment: $" << loan.amount / loan.months << std::endl;
                std::cout << "Months: " << loan.months << " months" << std::endl;
                std::cout << "Interest rate: " << loan.interest << "%" << std::endl;
                std::cout << std::endl;

                if (confirm("Confirm loan?")) {
                    handler.loan.create(loan, account);
                    std::cout << "Loan successful!" << std::endl;
                } else {
                    std::cout << "Loan cancelled!" << std::endl;
                }

                pause("Press Enter to go back...");
                break;
            case 3:
                double payAmount;
                std::cout << std::endl;
                std::cout << "Enter amount to pay: $";
                std::cin >> payAmount;
                err = handler.loan.pay(loan, account, payAmount);
                if (!err)
                    std::cout << "Total amount payed: $" << loan.payed << std::endl;
                else if (err == 1)
                    std::cout << "Amount is greater than loan amount" << std::endl;
                else if (err == 2)
                    std::cout << "You don't have enough money to pay that amount." << std::endl;
                else if (err == 3)
                    std::cout << "Amount is greater than remaining loan amount." << std::endl;
                std::cout << std::endl;
                pause("Press Enter to go back...");
                break;
            // case 4:
            //     std::cout << "Loan History: Work in Progress..." << std::endl;
            //     std::cout << std::endl;
            //     pause("Press Enter to go back...");
            //     break;
            case 4:
                return;
        }
    }
}

int Personal(Account& account, Handler& handler, Database& database) {
    struct Loan loan;
    handler.loan.current(loan, account.id);
    std::string check = "id = '" + account.id + "'";
    int hasLoan = database.select("loans", {"*"}, check).size();
    int choice = 0;
    int choice2 = 0;
    int deleted = 0;
    while (!deleted) {
        clear();
        handler.account.update(account, account.id);
        std::cout << "----- Account Options -----   ----- " << account.name.user
                  << " -----   ----- Balance: $" << account.balance.savings << " -----" << std::endl;
        std::cout << "\nOPTIONS:   [1] Refresh   [2] Edit   [3] Delete   [4] Back";

        std::cout << "\n";
        std::cout << "\nAccount Details -------" << std::endl;
        std::cout << "ID: " << account.id << std::endl;
        std::cout << "First Name: " << account.name.first << std::endl;
        std::cout << "Middle Name: " << account.name.middle << std::endl;
        std::cout << "Last Name: " << account.name.last << std::endl;

        if (hasLoan) {
            std::cout << "\nLoan Details ----------" << std::endl;
            std::cout << "Amount: $" << loan.amount << std::endl;
            std::cout << "Payed: $" << loan.payed << std::endl;
            std::cout << "Monthly Payment: $" << loan.amount / loan.months << std::endl;
            std::cout << "Interest: " << loan.interest << "%" << std::endl;
            std::cout << "Months: " << loan.months << std::endl;
            std::cout << "Months Left: " << loan.months_left << std::endl;
            std::cout << "Created: " << loan.date.toString("full") << std::endl;
        }

        std::cout << "\nSecurity Details ------" << std::endl;
        std::cout << "Expiration: " << (account.expiry.month < 10 ? "0" : "") << account.expiry.month << "/" << account.expiry.year << std::endl;
        std::cout << "CVC: " << account.cvc << std::endl;
        std::cout << "PIN: " << account.pin << std::endl;

        std::cout << std::endl;
        std::cout << "\n>> ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                break;
            case 2:
                do {
                    clear();
                    std::cout << "----- Editing Account -----   ----- " << account.name.user
                              << " -----   ----- Balance: $" << account.balance.savings << " -----" << std::endl;
                    std::cout << "\nOPTIONS:   [1] First   [2] Middle   [3] Last   [4] Username   [5] PIN   [6] Save   [7] Back";
                    std::cout << std::endl;
                    std::cout << "ID: " << account.id << std::endl;
                    std::cout << "Username: " << account.name.user << std::endl;
                    std::cout << "First Name: " << account.name.first << std::endl;
                    std::cout << "Middle Name: " << account.name.middle << std::endl;
                    std::cout << "Last Name: " << account.name.last << std::endl;
                    std::cout << "PIN: " << account.pin << std::endl;

                    std::cout << "\nSelect an option to edit";
                    std::cout << "\n>> ";
                    std::cin >> choice2;
                    std::cout << std::endl;

                    switch (choice2) {
                        case 1:
                            std::cout << "Enter new first name: ";
                            std::cin >> account.name.first;
                            break;
                        case 2:
                            std::cout << "Enter new middle name: ";
                            std::cin >> account.name.middle;
                            break;
                        case 3:
                            std::cout << "Enter new last name: ";
                            std::cin >> account.name.last;
                            break;
                        case 4:
                            std::cout << "Enter new username: ";
                            std::cin >> account.name.user;
                            break;
                        case 5:
                            std::cout << "Enter new PIN: ";
                            std::cin >> account.pin;
                            break;
                        case 6:
                            handler.account.edit(account);
                            pause("Account updated! Press Enter to continue...");
                            break;
                        case 7:
                            handler.account.update(account, account.id);
                            break;
                        default:
                            pause("Invalid option! Press Enter to try again...");
                            break;
                    }
                } while (choice2 != 7);
                break;
            case 3:
                deleted = 1;
                handler.account.remove(account.id);
                break;
            case 4:
                return deleted;
        }
    }
    return deleted;
}

void Logout(Account& account, Handler& handler) {
    std::cout << "Logging out..." << std::endl;
    handler.account.logout(account);

    std::cout << std::endl;
    std::cout << "Logged out successfully!" << std::endl;
    pause("Press Enter to continue...");
}

void Delete(Account& account, Handler& handler) {
    std::cout << "Deleting account..." << std::endl;
    handler.account.remove(account.id);

    std::cout << std::endl;
    std::cout << "Account deleted successfully!" << std::endl;
    pause("\nPress enter to continue...");
}

int loop(Handler& handler, Account& account, Database& database) {
    int choice = 0;
    while (choice != -1) {
        clear();
        std::cout << "----- Welcome to AATMS -----" << std::endl;
        std::cout << "\nOPTIONS:   [1] Login   [2] Create Account";
        std::cout << "\n>> ";
        std::cin >> choice;
        std::cout << std::endl;

        int deleted = 0;
        switch (choice) {
            case 1: {
                int err = Login(account, handler);

                if (!err) {
                    int accountOption = -1;
                    while (accountOption != 7 && !deleted) {
                        clear();
                        std::cout << "----- Account Options -----   ----- " << account.name.user
                                  << " -----   ----- Balance: $" << account.balance.savings << " -----" << std::endl;
                        std::cout << "\nOPTIONS:   [1] Refresh   [2] Deposit   [3] Withdraw   [4] Transfer   [5] Loan   [6] Account   [7] Logout";
                        std::cout << "\n>> ";
                        std::cin >> accountOption;

                        std::cout << std::endl;
                        switch (accountOption) {
                            case 1:
                                handler.account.update(account, account.id);
                                break;
                            case 2:
                                Deposit(account, handler);
                                break;
                            case 3:
                                Withdraw(account, handler);
                                break;
                            case 4:
                                Transfer(account, handler, database);
                                break;
                            case 5:
                                Loan(account, handler);
                                break;
                            case 6:
                                deleted = Personal(account, handler, database);
                                break;
                            case 7:
                                Logout(account, handler);
                                choice = 0;
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
                Create(account, handler);
                break;
            }
            case -1: {
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

    loop(handler, account, database);

    database.closeDB();

    return 0;
}