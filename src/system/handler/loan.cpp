#include "../handler.h"

Handler::HandLoan::HandLoan(const Handler& thisHandler)
    : handler(const_cast<Handler&>(thisHandler)) {
}

int Handler::HandLoan::create(struct Loan& loan, Account& account) {
    std::string check, id;
    do {
        // std::cout << "Generating ID...";
        id = handler.generate.id(true, 10);
        check = "reference = '" + id + "'";
        // std::cout << "[" << id << "]" << std::endl;
    } while (handler.database.select("loans", {"reference", "type", "id"}, check).size() > 0);

    loan.reference = id;
    loan.id = account.id;
    loan.type = "create";
    loan.payed = 0;
    loan.months_left = loan.months;
    loan.strikes = 0;
    loan.date = handler.generate.getDate();

    check = "reference = '" + loan.reference + "' AND type = '" + loan.type + "' AND id = '" + account.id + "'";
    if (handler.database.select("loans", {"reference", "id", "type"}, check).size() > 0) {
        // std::cerr << "[ERROR] Loan already exists" << std::endl;
        return 1;
    }

    handler.database.insert(
        "loans",
        {"reference", "id", "type", "amount", "payed", "interest", "months", "months_left", "strikes", "date"},
        {loan.reference, loan.id, loan.type, std::to_string(loan.amount), std::to_string(loan.payed), std::to_string(loan.interest), std::to_string(loan.months), std::to_string(loan.months_left), std::to_string(loan.strikes), loan.date.toString("full")});

    current(loan, account.id);
    return 0;
}

std::vector<std::vector<double>> Handler::HandLoan::getOptions(double amount) {
    std::vector<std::vector<double>> loanOptions;
    double totalAmount = 0;

    // Example loan options with different interest rates and durations
    totalAmount = calculateTotalAmount(amount, 10, 12);  // 10% interest rate for 12 months
    std::vector<double> loanOption1 = {totalAmount, 12, 10};
    totalAmount = calculateTotalAmount(amount, 12, 24);  // 12% interest rate for 24 months
    std::vector<double> loanOption2 = {totalAmount, 24, 12};
    totalAmount = calculateTotalAmount(amount, 15, 36);  // 15% interest rate for 36 months
    std::vector<double> loanOption3 = {totalAmount, 36, 15};
    totalAmount = calculateTotalAmount(amount, 18, 48);  // 18% interest rate for 48 months
    std::vector<double> loanOption4 = {totalAmount, 48, 18};
    totalAmount = calculateTotalAmount(amount, 20, 60);  // 20% interest rate for 60 months
    std::vector<double> loanOption5 = {totalAmount, 60, 20};

    if (amount >= 1000) {
        loanOptions.push_back(loanOption1);
        loanOptions.push_back(loanOption2);
    }
    if (amount > 5000) {
        loanOptions.push_back(loanOption3);
    }
    if (amount > 10000) {
        loanOptions.push_back(loanOption4);
    }
    if (amount > 15000) {
        loanOptions.push_back(loanOption5);
    }
    return loanOptions;
};

double Handler::HandLoan::calculateTotalAmount(double amount, double interestRate, int months) {
    double totalAmount = amount * (1 + (interestRate / 100) * (months / 12.0));
    return totalAmount;
}

int Handler::HandLoan::current(Loan& loan, std::string id) {
    DateTime convert;
    std::string check = "id = '" + id + "'";
    std::vector<RowData> result = handler.database.select("loans", {"*"}, check);
    int size = result.size();

    if (size > 0) {
        std::vector<std::string> data = result[0].columnValues;
        loan.reference = data[0];
        loan.id = data[1];
        loan.type = data[2];
        loan.amount = std::stod(data[3]);
        loan.payed = std::stod(data[4]);
        loan.interest = std::stod(data[5]);
        loan.months = std::stoi(data[6]);
        loan.months_left = std::stoi(data[7]);
        loan.strikes = std::stoi(data[8]);
        loan.date = convert.fromString(data[9]);
        return size;
    }

    return size;
}

int Handler::HandLoan::pay(struct Loan& loan, Account& account, double amount) {
    current(loan, account.id);

    if (amount > loan.amount) {
        // std::cerr << "[ERROR] Amount is greater than loan amount" << std::endl;
        return 1;
    }

    if (amount > account.balance.savings) {
        // std::cerr << "[ERROR] Amount is greater than account balance" << std::endl;
        return 2;
    }

    if (amount > loan.amount - loan.payed) {
        // std::cerr << "[ERROR] Amount is greater than remaining loan amount" << std::endl;
        return 3;
    }

    loan.payed += amount;
    account.balance.savings -= amount;

    handler.database.update("loans", {"payed"}, {std::to_string(loan.payed)}, "reference = '" + loan.reference + "'");
    handler.database.update("accounts", {"savings"}, {std::to_string(account.balance.savings)}, "id = '" + account.id + "'");

    return 0;
}

/**
 * @brief Calculate possible loan options
 *
 * @param loan Loan object
 * @param account Account object
 * @param strikePenalty Penalty factor for strikes (recommended: 0.2)
 * @param maxLoanFactor Maximum loan amount factor (recommended: 5.0)
 * @param minSalary // Minimum salary required (recommended: 30000)
 * @param minMembershipDays // Minimum membership duration in days (recommended: 30)
 * @param maxOptions // Maximum number of loan options
 * @return std::vector<std::vector<int>> Loan Options
 */
std::vector<std::vector<int>> Handler::HandLoan::calculateLoanOptions(struct Loan& loan, Account& account, double strikePenalty, double maxLoanFactor, double minSalary, int minMembershipDays, int maxOptions) {
    std::vector<std::vector<int>> loanOptions;
    // defaults
    // strikePenalty = strikePenalty ? strikePenalty : 0.2;             // Penalty factor for strikes
    // maxLoanFactor = maxLoanFactor ? maxLoanFactor : 5.0;             // Maximum loan amount factor
    // minSalary = minSalary ? minSalary : 30000.0;                     // Minimum salary required
    // minMembershipDays = minMembershipDays ? minMembershipDays : 30;  // Minimum membership duration in days
    // maxOptions = maxOptions ? maxOptions : 5;                        // Maximum number of loan options

    // Check if salary is above the minimum threshold
    if (account.salary >= minSalary) {
        // Check if membership duration is at least one month
        DateTime currentTime = handler.generate.getDate();

        double membershipDays = currentTime.compare(account.date.created);

        if (membershipDays >= minMembershipDays) {
            // Calculate the loan amounts, months, and interest rates based on salary and strikes
            double maxLoanAmount = account.salary * maxLoanFactor;  // Maximum loan amount
            int months = 12;                                        // Default number of months
            double interestRate = 10.0;                             // Default interest rate
            double interestRateIncrement = 1.0 / maxOptions;        // Balanced interest rate increment

            for (int i = 0; i <= loan.strikes; i++) {
                double calculatedLoanAmount = maxLoanAmount * (1 - i * strikePenalty);
                double rate = pow((calculatedLoanAmount / loan.amount), (1.0 / months));
                int calculatedInterestRate = static_cast<int>((1 - rate) * 100);
                std::vector<int> loanOption = {static_cast<int>(calculatedLoanAmount), months, calculatedInterestRate};
                loanOptions.push_back(loanOption);

                if (loanOptions.size() >= maxOptions) {
                    break;  // Maximum number of loan options reached
                }

                // Adjust the values for the next loan option
                months += 6;                            // Increment by 6 months
                interestRate += interestRateIncrement;  // Increment by balanced interest rate increment
            }
        }
    }

    // print loan options
    // std::cout << "Loan Options:" << std::endl;
    // for (int i = 0; i < loanOptions.size(); i++) {
    //     std::cout << "Option " << i + 1 << ": " << std::endl;
    //     std::cout << "Amount: " << loanOptions[i][0] << std::endl;
    //     std::cout << "Months: " << loanOptions[i][1] << std::endl;
    //     std::cout << "Interest Rate: " << loanOptions[i][2] << std::endl;
    // }

    return loanOptions;
}