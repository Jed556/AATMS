#include "system/AATMS.h"

int WinMain(int argc, char const* argv[]) {
    Account account;
    Database database("../database/database.db");
    Handler handler(database);
    database.openDB();
    database.create("accounts", {"id", "first", "middle", "last", "user", "cvc", "pin", "month", "year", "loan", "savings", "created", "login", "logout"});

    std::string firstName, lastName, pin;
    std::cout << "Enter first name: ";
    std::cin >> firstName;
    std::cout << "Enter last name: ";
    std::cin >> lastName;
    std::cout << "Enter PIN: ";
    std::cin >> pin;

    Name name = {"Jerrald", "Josue", "Guiriba", "Jed556"};
    handler.account.create(account, name, "1234");

    system("pause");

    return 0;
}