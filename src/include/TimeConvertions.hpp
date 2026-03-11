#pragma once

#include <cstdint>
#include <chrono>
#include <string>
#include <sstream>

using TimeStampAlignType = int64_t;

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

inline TimeStampAlignType parse_to_timestamp(const std::string& input, const std::string& fmt) {
    std::stringstream ss(input);
    std::chrono::sys_seconds tp;
    ss >> std::chrono::parse(fmt, tp);

    if (ss.fail()) {
        throw std::runtime_error("Failed to parse: " + input);
    }

    return tp.time_since_epoch().count();
}
inline TimeStampAlignType parse_datetime(const std::string& input) {
    return parse_to_timestamp(input, "%Y-%m-%dT%H:%M:%S");
}
inline TimeStampAlignType parse_date(const std::string& input) {
    return parse_to_timestamp(input + "T00:00:00", "%Y-%m-%dT%H:%M:%S");
}
inline TimeStampAlignType parse_time(const std::string& input) {
    return parse_to_timestamp("T00:00:00" + input, "%Y-%m-%dT%H:%M:%S");
}

constexpr int64_t SEC_PER_DAY = 86400;
constexpr int64_t SEC_PER_HOUR = 3600;

inline DateTimeInfo single_convert(const TimeStampAlignType timestamp) {
    DateTimeInfo info{};

    const TimeStampAlignType seconds_of_day = timestamp % SEC_PER_DAY;
    info.second = seconds_of_day % 60;
    info.minute = (seconds_of_day / 60) % 60;
    info.hour   = seconds_of_day / SEC_PER_HOUR;

    const std::chrono::sys_days sd(std::chrono::days(timestamp / SEC_PER_DAY));
    const std::chrono::year_month_day ymd{sd};

    info.year  = static_cast<int>(ymd.year());
    info.month = static_cast<unsigned>(ymd.month());
    info.day   = static_cast<unsigned>(ymd.day());

    // Day of Week: ISO encoding (Mon=1 ... Sun=7)
    // The raw math is (days_since_epoch + 4) % 7 or similar, but C++20 is clean:
    const std::chrono::weekday wd{sd};
    info.day_of_week = wd.iso_encoding();

    // Day of Year
    // We create a date for Jan 1st of THIS year.
    const auto first_day_of_year = std::chrono::sys_days(std::chrono::year_month_day(ymd.year(), std::chrono::month(1), std::chrono::day(1)));
    // Subtracting two sys_days gives a duration in days
    info.day_of_year = (sd - first_day_of_year).count() + 1;

    // This is the "Simple" definition (Jan 1 is Week 1)
    info.week_of_year = (info.day_of_year + 6) / 7;
    return info;
}

inline std::vector<DateTimeInfo> batch_convert(const std::vector<TimeStampAlignType>& timestamps) {
    std::vector<DateTimeInfo> results;
    results.reserve(timestamps.size()); // Critical: Avoid reallocations

    for (const auto ts : timestamps) {
        DateTimeInfo info = single_convert(ts);
        results.emplace_back(info);
    }

    return results;
}

inline double get_year(const TimeStampAlignType timestamp) {
    const std::chrono::sys_days sd(std::chrono::days(timestamp / SEC_PER_DAY));
    const std::chrono::year_month_day ymd{sd};
    return static_cast<double>(static_cast<int>(ymd.year()));
}
inline double get_day_of_year(const TimeStampAlignType timestamp) {
    const std::chrono::sys_days sd(std::chrono::days(timestamp / SEC_PER_DAY));
    const std::chrono::year_month_day ymd{sd};
    const auto first_day_of_year = std::chrono::sys_days(std::chrono::year_month_day(ymd.year(), std::chrono::month(1), std::chrono::day(1)));
    return (sd - first_day_of_year).count() + 1;
}
inline double get_month(const TimeStampAlignType timestamp){
    const std::chrono::sys_days sd(std::chrono::days(timestamp / SEC_PER_DAY));
    const std::chrono::year_month_day ymd{sd};
    return static_cast<double>(static_cast<unsigned>(ymd.month()));
}
inline double get_day(const TimeStampAlignType timestamp){
    const std::chrono::sys_days sd(std::chrono::days(timestamp / SEC_PER_DAY));
    const std::chrono::year_month_day ymd{sd};
    return static_cast<double>(static_cast<unsigned>(ymd.day()));
}
inline double get_day_of_week(const TimeStampAlignType timestamp){
    const std::chrono::sys_days sd(std::chrono::days(timestamp / SEC_PER_DAY));
    const std::chrono::weekday wd{sd};
    return wd.iso_encoding();
}
inline double get_week_of_year(const TimeStampAlignType timestamp) {
    const auto day_of_year = get_day_of_year(timestamp);
    return (day_of_year + 6) / 7;
}
inline double get_hour(const TimeStampAlignType timestamp) {
    const auto seconds_of_day = static_cast<double>(timestamp % SEC_PER_DAY);
    return seconds_of_day / SEC_PER_HOUR;
}
inline double get_minute(const TimeStampAlignType timestamp) {
    const auto seconds_of_day = timestamp % SEC_PER_DAY;
    return static_cast<double>((seconds_of_day / 60) % 60);
}
inline double get_second(const TimeStampAlignType timestamp) {
    const auto seconds_of_day = timestamp % SEC_PER_DAY;
    return static_cast<double>(seconds_of_day % 60);
}
inline double get_second_of_day(const TimeStampAlignType timestamp) {
    return static_cast<double>(timestamp % SEC_PER_DAY);
}