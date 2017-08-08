#include "Student.hpp"
#include "CSVReader.hpp"
#include "Weekday.hpp"
#include <iostream>
#include <map>
using namespace std;



uint16_t Student::isTally = 0;

Student::Student(CSVReader* pnFile) :
    icNumber(isTally++), iInversed(false)
{
    pnFile->nextCell(&iEmail);
    trimEmail(iEmail);
    pnFile->nextCell(&iName);
    pnFile->nextCell(&iInstrument);
    pnFile->nextCell(&iPrefEmail);
    trimEmail(iPrefEmail);

    if (iInstrument == "Piano") pnFile->nextCell(&iPrefInstrument);
    else pnFile->nextCell(CSVReader::Skip::COLUMN);
    
    string hYesNo;
    do
    {
        TimeSeg hTimeSeg(pnFile);
        iTimeSegs.push_back(hTimeSeg);
        pnFile->nextCell(&hYesNo);
    } while (hYesNo == "Yes" && iTimeSegs.size() < 10);
}


Student::~Student()
{
}


string Student::getName() const
{
    return iName;
}


string Student::getEmail() const
{
    return iEmail;
}


string Student::getInstrument() const
{
    return iInstrument;
}


string Student::getPrefEmail() const
{
    return iPrefEmail;
}


string Student::getPrefInstrument() const
{
    return iPrefInstrument;
}


const vector<TimeSeg>& Student::getTimeSegs() const
{
    return iTimeSegs;
}


void Student::inverseTimeSegs()
{
    map<Weekday, bool> tDayTally;
    
    for (TimeSeg& lfTimeSeg : iTimeSegs)
    {
        lfTimeSeg.inverse();

        for (const Weekday& lcfDays : lfTimeSeg.getDays())
        {
            tDayTally[lcfDays] = true;
        }
    }

    // Add unaccounted for days
    if (!iInversed)
    {
        for (uint8_t lDays=0; lDays != Weekday::INVALID; lDays++)
        {
            if (tDayTally[(Weekday) lDays] == false)
            {
                TimeSeg hFullDay((Weekday) lDays, 0, 1439);
                iTimeSegs.push_back(hFullDay);
            }
        }
    }
    // Remove unaccounted for days
    else
    {
        for (uint8_t i=0; i<iTimeSegs.size(); )
        {
            if (iTimeSegs[i].getStartTime() == 0 &&
                    iTimeSegs[i].getEndTime() == 1439)
            {
                iTimeSegs.erase(iTimeSegs.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }

    iInversed = !iInversed;
}


bool Student::isInversed() const
{
    return iInversed;
}


void Student::printInfo() const
{
    cout << "Email:  " << iEmail << endl;
    cout << "Name:   " << iName << endl;
    cout << "Instru: " << iInstrument << endl;
    cout << "PrEml:  " << iPrefEmail << endl;
    cout << "PrIstr: " << iPrefInstrument << endl;

    for (const TimeSeg& lcfTimeSeg : iTimeSegs)
    {
        lcfTimeSeg.printInfo();
    }
}


void Student::trimEmail(string& pfEmail)
{
    pfEmail = pfEmail.substr(0, pfEmail.find("@"));
}
