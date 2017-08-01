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

    uint16_t getStartTime() const;
    uint16_t getEndTime() const;

    bool isOverlap(const TimeSeg* pcnOther) const;
    void printInfo() const;

private:
    uint16_t iStartTime, iEndTime;
    std::vector<Weekday> iDays;
};

#endif // TIMESEG_HPP
