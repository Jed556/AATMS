CREATE TABLE IF NOT EXISTS accounts (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    first TEXT NOT NULL,
    middle TEXT NOT NULL,
    last TEXT NOT NULL,
    user TEXT NOT NULL,
    cvc TEXT NOT NULL,
    pin TEXT NOT NULL,
    month INTEGER NOT NULL,
    year INTEGER NOT NULL,
    loan REAL NOT NULL,
    savings REAL NOT NULL,
    created TEXT NOT NULL,
    login TEXT NOT NULL,
    logout TEXT NOT NULL
);
INSERT INTO accounts (
        id,
        first,
        middle,
        last,
        user,
        cvc,
        pin,
        month,
        year,
        loan,
        savings,
        created,
        login,
        logout
    )
VALUES (
        9,
        'first_value',
        'middle_value',
        'last_value',
        'user_value',
        'cvc_value',
        'pin_value',
        1,
        23,
        5.0,
        7.0,
        'created_value',
        'login_value',
        'logout_value'
    );
SELECT *
FROM accounts;
SELECT *
FROM loans;
SELECT *
FROM history;