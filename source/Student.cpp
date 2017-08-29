#include "Student.hpp"
#include "CSVReader.hpp"
#include "util.hpp"
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
    pnFile->nextCell(&iProfEmail);
    trimEmail(iProfEmail);
    pnFile->nextCell(&iName);
    pnFile->nextCell(&iInstrument);

    TimeSeg hLesson(pnFile);
    iLesson = hLesson;
    
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


TimeSeg Student::getLesson() const
{
    return iLesson;
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
    cout << "Name:                " << iName << endl;
    cout << "Instrument:          " << iInstrument << endl;
    cout << "Lesson Time:         "; iLesson.printInfo();
    cout << "Email:               " << iEmail << endl;
    cout << "Prof Email:          " << iProfEmail << endl;
    cout << "Pref Partner/Prof:   " << iPrefEmail << endl;
    cout << "Pref Instrument:     " << iPrefInstrument << endl;

    cout << "Obligations:" << endl;
    for (const TimeSeg& lcfTimeSeg : iTimeSegs)
    {
        cout << "    ";
        lcfTimeSeg.printInfo();
    }
}


uint16_t Student::scoreOverlap(const Student* pnOther) const
{
    // hScoreBuffer helps make sure that the time segment overlap is at least
    //   n minutes long. It doesn't help if two people's free time overlaps
    //   by only a couple minutes... IMHO, the time overlap should be at least
    //   30 minutes.
    uint16_t rOverlap = 0, hScoreBuffer = 0;
    
    if (pnOther)
    {
        for (uint8_t lDay=0; lDay!=Weekday::INVALID; lDay++)
        {
            // Sweep from 9AM to 9PM
            for (uint16_t lTime=540; lTime<1261; lTime++)
            {
                if (stuSegDuring(lTime, (Weekday) lDay, *this) &&
                        stuSegDuring(lTime, (Weekday) lDay, *pnOther))
                {
                    hScoreBuffer++;
                }
                else
                {
                    if (hScoreBuffer >= 30)
                    {
                        rOverlap += hScoreBuffer;
                    }

                    hScoreBuffer = 0;
                }
            }
            
            if (hScoreBuffer >= 30)
            {
                rOverlap += hScoreBuffer;
            }
        }
    }
    
    return rOverlap;
}


bool Student::canAttendLesson(const Student* pnOther) const
{
    uint16_t hScore = 0, hScoreBuffer = 0;
    for (uint16_t lTime=pnOther->getLesson().getStartTime();
            lTime < pnOther->getLesson().getEndTime(); lTime++)
    {
        if (!stuSegDuring(lTime, pnOther->getLesson().getDays()[0], *this))
        {
            hScoreBuffer++;
        }
        else
        {
            if (hScoreBuffer >= 20)
            {
                hScore += hScoreBuffer;
            }

            hScoreBuffer = 0;
        }
    }
    
    if (hScoreBuffer >= 20)
    {
        hScore += hScoreBuffer;
    }

    if (hScore >= 20)
    {
        return true;
    }

    return false;
}


void Student::trimEmail(string& pfEmail)
{
    pfEmail = pfEmail.substr(0, pfEmail.find("@"));
}
