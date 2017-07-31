#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdint>
#include <string>
#include <vector>



enum Weekday
{
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    INVALID
};

std::string cfill(std::string prFillMe, const char& pcfFillWith,
        const bool& pcfFillLeft, const uint16_t& pcfFillLen);

// string to time; string to day
std::uint16_t stotime(const std::string& pcfStr);
Weekday stoday(const std::string& pcfStr);
void stoday(const std::string& pcfStr, std::vector<Weekday>* pnDays);

// time to string; day to string
std::string timetos(const std::uint16_t& pcfInt);
std::string daytos(const Weekday& pcfDay);

#endif // UTIL_HPP
