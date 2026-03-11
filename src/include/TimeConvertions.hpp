#pragma once

#include <cstdint>
#include <chrono>
#include <string>

struct alignas(16) DateTimeInfo {
    uint16_t year;          // 0-65535
    uint16_t day_of_year;   // 1-366
    uint8_t  month;         // 1-12
    uint8_t  day;           // 1-31
    uint8_t  day_of_week;   // 1-7 (Mon-Sun)
    uint8_t  week_of_year;  // 1-53
    uint8_t  hour;          // 0-23
    uint8_t  minute;        // 0-59
    uint8_t  second;        // 0-59
    // Padding: 7 bytes
};

uint64_t parse_to_timestamp(const std::string& input, const std::string& fmt);
uint64_t parse_datetime(const std::string& input);
uint64_t parse_date(const std::string& input);
uint64_t parse_time(const std::string& input);

constexpr int64_t SEC_PER_DAY = 86400;
constexpr int64_t SEC_PER_HOUR = 3600;

std::vector<DateTimeInfo> batch_convert(const std::vector<uint64_t>& timestamps);
DateTimeInfo single_convert(const uint64_t timestamp);

double get_year(const uint64_t timestamp);
double get_day_of_year(const uint64_t timestamp);
double get_month(const uint64_t timestamp);
double get_day(const uint64_t timestamp);
double get_day_of_week(const uint64_t timestamp);
double get_week_of_year(const uint64_t timestamp);
double get_hour(const uint64_t timestamp);
double get_minute(const uint64_t timestamp);
double get_second(const uint64_t timestamp);
double get_second_of_day(const uint64_t timestamp);