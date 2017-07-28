#include <cstdint>
#include <string>



enum Weekday
{
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY
};

std::uint16_t stotime(const std::string& pcfStr);

std::string timetos(const std::uint16_t& pcfInt);
