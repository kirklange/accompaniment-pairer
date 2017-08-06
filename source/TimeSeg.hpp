#ifndef TIMESEG_HPP
#define TIMESEG_HPP

#include "Weekday.hpp"
#include <cstdint>
#include <vector>

class CSVReader;



class TimeSeg
{
public:
    TimeSeg(CSVReader* pnFile);
    TimeSeg(const Weekday& pcfDay,
            const uint16_t& pcfStartTime, const uint16_t& pcfEndTime);
    virtual ~TimeSeg();

    // Start -> End ; End -> Start
    // Good for converting from free time to busy time
    void inverse();
    
    uint16_t getStartTime() const;
    uint16_t getEndTime() const;
    const std::vector<Weekday>& getDays() const;
    
    void printInfo() const;

private:
    uint16_t iStartTime, iEndTime;
    std::vector<Weekday> iDays;
};

#endif // TIMESEG_HPP
