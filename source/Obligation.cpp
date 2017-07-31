#include "Obligation.hpp"
#include "CSVReader.hpp"
#include <iostream>
#include <string>
using namespace std;



Obligation::Obligation(CSVReader* pnFile)
{
    string hData;
    pnFile->nextCell(&hData);
    stoday(hData, &iDays);

    pnFile->nextCell(&hData);
    iStartTime = stotime(hData);

    pnFile->nextCell(&hData);
    iEndTime = stotime(hData);
}


Obligation::~Obligation()
{
}


bool Obligation::isOverlap(const Obligation* pcnOther) const
{
    bool hDayMatch = false;
    for (const Weekday& lcfMeDay : iDays)
    {
        if (!hDayMatch)
        {
            for (const Weekday& lcfOtherDay : pcnOther->iDays)
            {
                if (lcfMeDay == lcfOtherDay)
                {
                    hDayMatch = true;
                    break;
                }
            }
        }
    }

    bool hMeOverOther =
        (iStartTime > pcnOther->iStartTime &&
         iStartTime < pcnOther->iEndTime) ||
        (iEndTime > pcnOther->iStartTime &&
         iEndTime < pcnOther->iEndTime);

    return hDayMatch && (hMeOverOther || pcnOther->isOverlap(this));
}


void Obligation::printInfo() const
{
    for (const Weekday& lcfDays : iDays)
    {
        cout << daytos(lcfDays) << ", ";
    }

    cout << "from " << timetos(iStartTime) <<
        " to " << timetos(iEndTime) << endl;
}
