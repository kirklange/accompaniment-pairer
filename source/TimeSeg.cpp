#include "TimeSeg.hpp"
#include "CSVReader.hpp"
#include "util.hpp"
#include <iostream>
#include <string>
using namespace std;



TimeSeg::TimeSeg(CSVReader* pnFile)
{
    string hData;
    pnFile->nextCell(&hData);
    stoday(hData, &iDays);

    pnFile->nextCell(&hData);
    iStartTime = stotime(hData);

    pnFile->nextCell(&hData);
    iEndTime = stotime(hData);
    // To compensate for the sweep algorithm
    iEndTime -= 1;
}

TimeSeg::TimeSeg(const Weekday& pcfDay,
        const uint16_t& pcfStartTime, const uint16_t& pcfEndTime) :
    iStartTime(pcfStartTime), iEndTime(pcfEndTime - 1)
{
    iDays.push_back(pcfDay);
}

TimeSeg::~TimeSeg()
{
}


void TimeSeg::inverse()
{
    uint16_t hOldStartTime = iStartTime;
    iStartTime = iEndTime;
    iEndTime = hOldStartTime;
}


uint16_t TimeSeg::getStartTime() const
{
    return iStartTime;
}


uint16_t TimeSeg::getEndTime() const
{
    return iEndTime;
}

const vector<Weekday>& TimeSeg::getDays() const
{
    return iDays;
}


void TimeSeg::printInfo() const
{
    for (const Weekday& lcfDays : iDays)
    {
        cout << daytos(lcfDays) << ", ";
    }

    cout << "from " << timetos(iStartTime) <<
        " to " << timetos(iEndTime) << endl;
}
