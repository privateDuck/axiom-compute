
#include "TimeConvertions.hpp"
#include <sstream>

using namespace std::chrono;

uint64_t parse_to_timestamp(const std::string& input, const std::string& fmt) {
    std::stringstream ss(input);
    sys_seconds tp;
    ss >> parse(fmt, tp);

    if (ss.fail()) {
        throw std::runtime_error("Failed to parse: " + input);
    }

    return tp.time_since_epoch().count();
}

uint64_t parse_datetime(const std::string& input) {
    return parse_to_timestamp(input, "%Y-%m-%dT%H:%M:%S");
}

uint64_t parse_date(const std::string& input) {
    return parse_to_timestamp(input + "T00:00:00", "%Y-%m-%dT%H:%M:%S");
}

uint64_t parse_time(const std::string& input) {
    return parse_to_timestamp("T00:00:00" + input, "%Y-%m-%dT%H:%M:%S");
}

std::vector<DateTimeInfo> batch_convert(const std::vector<uint64_t> &timestamps) {
    std::vector<DateTimeInfo> results;
    results.reserve(timestamps.size()); // Critical: Avoid reallocations

    for (const uint64_t ts : timestamps) {
        DateTimeInfo info = single_convert(ts);
        results.emplace_back(info);
    }

    return results;
}

DateTimeInfo single_convert(const uint64_t timestamp) {
    DateTimeInfo info;

    const uint64_t seconds_of_day = timestamp % SEC_PER_DAY;
    info.second = seconds_of_day % 60;
    info.minute = (seconds_of_day / 60) % 60;
    info.hour   = seconds_of_day / SEC_PER_HOUR;

    const sys_days sd(days(timestamp / SEC_PER_DAY));
    const year_month_day ymd{sd};

    info.year  = static_cast<int>(ymd.year());
    info.month = static_cast<unsigned>(ymd.month());
    info.day   = static_cast<unsigned>(ymd.day());

    // Day of Week: ISO encoding (Mon=1 ... Sun=7)
    // The raw math is (days_since_epoch + 4) % 7 or similar, but C++20 is clean:
    const weekday wd{sd};
    info.day_of_week = wd.iso_encoding();

    // Day of Year
    // We create a date for Jan 1st of THIS year.
    const auto first_day_of_year = sys_days(year_month_day(ymd.year(), month(1), day(1)));
    // Subtracting two sys_days gives a duration in days
    info.day_of_year = (sd - first_day_of_year).count() + 1;

    // This is the "Simple" definition (Jan 1 is Week 1)
    info.week_of_year = (info.day_of_year + 6) / 7;
    return info;
}

double get_year(const uint64_t timestamp) {
    const sys_days sd(days(timestamp / SEC_PER_DAY));
    const year_month_day ymd{sd};
    return static_cast<double>(static_cast<int>(ymd.year()));
}

double get_day_of_year(const uint64_t timestamp) {
    const sys_days sd(days(timestamp / SEC_PER_DAY));
    const year_month_day ymd{sd};
    const auto first_day_of_year = sys_days(year_month_day(ymd.year(), month(1), day(1)));
    return (sd - first_day_of_year).count() + 1;
}

double get_month(const uint64_t timestamp) {
    const sys_days sd(days(timestamp / SEC_PER_DAY));
    const year_month_day ymd{sd};
    return static_cast<double>(static_cast<unsigned>(ymd.month()));
}

double get_day(const uint64_t timestamp) {
    const sys_days sd(days(timestamp / SEC_PER_DAY));
    const year_month_day ymd{sd};
    return static_cast<double>(static_cast<unsigned>(ymd.day()));
}

double get_day_of_week(const uint64_t timestamp) {
    const sys_days sd(days(timestamp / SEC_PER_DAY));
    const weekday wd{sd};
    return wd.iso_encoding();
}

double get_week_of_year(const uint64_t timestamp) {
    const int day_of_year = static_cast<int>(get_day_of_year(timestamp));
    return (day_of_year + 6) / 7;
}

double get_hour(const uint64_t timestamp) {
    const uint64_t seconds_of_day = timestamp % SEC_PER_DAY;
    return seconds_of_day / SEC_PER_HOUR;
}

double get_minute(const uint64_t timestamp) {
    const uint64_t seconds_of_day = timestamp % SEC_PER_DAY;
    return (seconds_of_day / 60) % 60;
}

double get_second(const uint64_t timestamp) {
    const uint64_t seconds_of_day = timestamp % SEC_PER_DAY;
    return seconds_of_day % 60;
}

double get_seconds_of_day(const uint64_t timestamp) {
    return timestamp % SEC_PER_DAY;
}
