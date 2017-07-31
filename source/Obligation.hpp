#ifndef OBLIGATION_HPP
#define OBLIGATION_HPP

#include <cstdint>
#include <vector>
#include "util.hpp"

class CSVReader;



class Obligation
{
public:
    Obligation(CSVReader* pnFile);
    virtual ~Obligation();

    bool isOverlap(const Obligation* pcnOther) const;
    void printInfo() const;

private:
    uint16_t iStartTime, iEndTime;
    std::vector<Weekday> iDays;
};

#endif // OBLIGATION_HPP
