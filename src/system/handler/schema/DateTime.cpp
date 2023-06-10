#include "../../handler.h"

std::string DateTime::toString() const {
    std::string date = std::to_string(this->year) + "-" + std::to_string(this->month) + "-" + std::to_string(this->day);
    std::string time = std::to_string(this->hour) + ":" + std::to_string(this->minute) + ":" + std::to_string(this->second);
    return date + " " + time;
}