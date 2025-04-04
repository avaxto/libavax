/*
 * Copyright (C) 2025 REKTBuilder 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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