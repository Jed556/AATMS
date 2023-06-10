#include "../handler.h"

/**
 * @brief Get the current date
 *
 * @return DateTime Current date and time structure
 */
DateTime Generator::getDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    int year = 1900 + ltm->tm_year;
    int hour = ltm->tm_hour;
    int minute = ltm->tm_min;
    int second = ltm->tm_sec;

    // get the timezone
    char timezone_str[10];
    strftime(timezone_str, sizeof(timezone_str), "%z", ltm);
    std::string timezone = timezone_str;

    // get the milliseconds
    timeval tv;
    gettimeofday(&tv, NULL);
    int millisecond = tv.tv_usec / 1000;

    DateTime date = {month, day, year, hour, minute, second, millisecond, timezone};
    return date;
}