#include "TimeSeg.hpp"
#include "CSVReader.hpp"
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


TimeSeg::~TimeSeg()
{
}


uint16_t TimeSeg::getStartTime() const
{
    return iStartTime;
}


uint16_t TimeSeg::getEndTime() const
{
    return iEndTime;
}


uint16_t TimeSeg::getOverlapTime(const TimeSeg& pcfOther) const
{
    // Determine how many days overlap
    uint16_t hDaysMatch = 0;
    for (const Weekday& lcfMeDay : iDays)
    {
        for (const Weekday& lcfOtherDay : pcfOther.iDays)
        {
            if (lcfMeDay == lcfOtherDay)
            {
                hDaysMatch += 1;
            }
        }
    }

    // Sweep algorithm
    uint16_t rOverlap = 0;
    if (hDaysMatch > 0)
    {
        const uint16_t& a = iStartTime, b = iEndTime,
              x = pcfOther.iStartTime, y = pcfOther.iEndTime;
        for (uint16_t i=0; i<1440; i+=15)
        {
            if (a < b)
            {
                if (x < y)
                {
                    if (i >= a && i >= x && i <= b && i <= y)
                    {
                        rOverlap += 15;
                    }
                }
                else
                {
                    if ((i <= b && i >= x) || (i >= a && i <= y))
                    {
                        rOverlap += 15;
                    }
                }
            }
            else
            {
                if (x < y)
                {
                    if ((i <= y && i >= a) || (i >= x && i <= b))
                    {
                        rOverlap += 15;
                    }
                }
                else
                {
                    if ((i >= a && i >= x) || (i <= b && i <= y))
                    {
                        rOverlap += 15;
                    }
                }
            }
        }

        //rOverlap *= hDaysMatch;
        //rOverlap += ()
    }

    return rOverlap;
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
