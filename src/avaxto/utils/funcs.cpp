#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

std::string get_current_datetime() {
    std::ostringstream oss;
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

    oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");

    char tz = tm.tm_isdst > 0 ? 'D' : 'S'; // 'D' for Daylight Saving Time, 'S' for Standard Time
    oss << tz;

    return oss.str();
}