#ifndef TIMESEG_HPP
#define TIMESEG_HPP

#include <cstdint>
#include <vector>
#include "util.hpp"

class CSVReader;



class TimeSeg
{
public:
    TimeSeg(CSVReader* pnFile);
    virtual ~TimeSeg();

    // Start -> End ; End -> Start
    // Good for converting from free time to busy time
    void inverse();

    // Returns amount of minutes that this and other overlap
    uint16_t getOverlapTime(const TimeSeg& pcfOther) const;
    
    uint16_t getStartTime() const;
    uint16_t getEndTime() const;
    void printInfo() const;

private:
    uint16_t iStartTime, iEndTime;
    std::vector<Weekday> iDays;
    // When inversed, missing Weekdays count towards 24hrs worth of overlap 
    bool iInversed;
};

#endif // TIMESEG_HPP
