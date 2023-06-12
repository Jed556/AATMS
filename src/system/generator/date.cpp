#include "../handler.h"

/**
 * @brief Get the current date
 *
 * @return DateTime Current date and time structure
 */
DateTime Generator::getDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    tm* gmtm = gmtime(&now);

    // add 8 hours to the current time to get the Philippine time
    ltm->tm_hour += UTC;
    mktime(ltm);

    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    int year = 1900 + ltm->tm_year;
    int hour = ltm->tm_hour;
    int minute = ltm->tm_min;
    int second = ltm->tm_sec;

    // get the timezone
    std::string timezone = "UTC";
    if (UTC > 0) timezone += "+";
    timezone += std::to_string(UTC);

    // get the milliseconds
    timeval tv;
    gettimeofday(&tv, NULL);
    int millisecond = tv.tv_usec / 1000;

    DateTime date = {month, day, year, hour, minute, second, millisecond, timezone};
    // std::cout << date.toString("full") << std::endl;
    return date;
}