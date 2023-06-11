#include "../../handler.h"

std::string DateTime::toString(std::string which) const {
    std::transform(which.begin(), which.end(), which.begin(), ::tolower);

    std::string month = (this->month < 10) ? "0" + std::to_string(this->month) : std::to_string(this->month);
    std::string day = (this->day < 10) ? "0" + std::to_string(this->day) : std::to_string(this->day);
    std::string year = std::to_string(this->year);
    std::string hour = (this->hour < 10) ? "0" + std::to_string(this->hour) : std::to_string(this->hour);
    std::string minute = (this->minute < 10) ? "0" + std::to_string(this->minute) : std::to_string(this->minute);
    std::string second = (this->second < 10) ? "0" + std::to_string(this->second) : std::to_string(this->second);
    std::string millisecond = (this->millisecond < 10) ? "00" + std::to_string(this->millisecond) : (this->millisecond < 100) ? "0" + std::to_string(this->millisecond)
                                                                                                                              : std::to_string(this->millisecond);
    std::string date = month + "/" + day + "/" + year;
    std::string time = hour + ":" + minute + ":" + second;
    std::string zone = this->timezone;

    if (which == "date") {
        return date;
    } else if (which == "time") {
        return time;
    } else if (which == "datetime" || which == "dt") {
        std::string datetime = date + "-" + time;
        return datetime;
    } else if (which == "datetimezone" || which == "dtz" || which == "full") {
        std::string datetimezone = date + "-" + time + "-" + zone;
        return datetimezone;
    } else if (which == "monthday") {
        std::string monthday = std::to_string(this->month) + "/" + std::to_string(this->day);
        return monthday;
    } else if (which == "monthday2") {
        return month + "/" + day;
    } else if (which == "monthyear") {
        std::string monthyear = std::to_string(this->month) + "/" + std::to_string(this->year);
        return monthyear;
    } else if (which == "monthyear2") {
        return month + "/" + year;
    } else if (which == "month" || which == "mon") {
        return std::to_string(this->month);
    } else if (which == "day") {
        return std::to_string(this->day);
    } else if (which == "day2") {
        return day;
    } else if (which == "year" || which == "yr") {
        return std::to_string(this->year);
    } else if (which == "year2") {
        return year;
    } else if (which == "hour" || which == "hr") {
        return std::to_string(this->hour);
    } else if (which == "hour2") {
        return hour;
    } else if (which == "minute" || which == "min") {
        return std::to_string(this->minute);
    } else if (which == "minute2") {
        return minute;
    } else if (which == "second" || which == "sec") {
        return std::to_string(this->second);
    } else if (which == "second2") {
        return second;
    } else if (which == "millisecond") {
        return millisecond;
    } else if (which == "timezone" || which == "zone") {
        return timezone;
    }

    std::cerr << "Error: Invalid parameter" << std::endl;
    return "Error: Invalid parameter";
}

//reverse engineers a full date format from toString("full") 01/11/2021-12:00:00-UTC+8
DateTime DateTime::fromString(std::string datetimezone) {
    DateTime datetime;

    std::string month = datetimezone.substr(0, 2);
    std::string day = datetimezone.substr(3, 2);
    std::string year = datetimezone.substr(6, 4);
    std::string hour = datetimezone.substr(11, 2);
    std::string minute = datetimezone.substr(14, 2);
    std::string second = datetimezone.substr(17, 2);
    std::string timezone = datetimezone.substr(20, 5);

    datetime.month = std::stoi(month);
    datetime.day = std::stoi(day);
    datetime.year = std::stoi(year);
    datetime.hour = std::stoi(hour);
    datetime.minute = std::stoi(minute);
    datetime.second = std::stoi(second);
    datetime.timezone = timezone;

    return datetime;
}