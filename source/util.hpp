#ifndef UTIL_HPP
#define UTIL_HPP

#include "Student.hpp"
#include "Weekday.hpp"
#include <cstdint>
#include <string>
#include <vector>



std::string cfill(std::string prFillMe, const char& pcfFillWith,
        const bool& pcfFillLeft, const uint16_t& pcfFillLen);

// string to time; string to day
std::uint16_t stotime(std::string pStr);
Weekday stoday(const std::string& pcfStr);
void stoday(const std::string& pcfStr, std::vector<Weekday>* pnDays);

// time to string; day to string
std::string timetos(const std::uint16_t& pcfInt);
std::string daytos(const Weekday& pcfDay);

// Is Student NOT Available At Given Time?
bool stuSegDuring(const uint16_t& pcfTime,
        const Weekday& pcfDay, const Student& pcfStu);

#endif // UTIL_HPP
