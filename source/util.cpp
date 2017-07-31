#include "util.hpp"
#include <cmath>
using namespace std;



string cfill(string prFillMe, const char& pcfFillWith,
        const bool& pcfFillLeft, const uint16_t& pcfFillLen)
{
    while (prFillMe.length() < pcfFillLen)
    {
        if (pcfFillLeft)
        {
            prFillMe = pcfFillWith + prFillMe;
        }
        else
        {
            prFillMe = prFillMe + pcfFillWith;
        }
    }
    
    return prFillMe;
}


// SOME OF THE ASSUMPTIONS
//   1) First section is hour
//   2) Seconds section (if there is one) is always zero
//   3) Format is 12 hour AM/PM time
//   4) Minutes are to be rounded to the nearest 15
uint16_t stotime(const string& pcfStr)
{
    const string cNum = "0123456789";
    string hSectStr;
    bool gParseHour = true, gFrontDigit = true;
    uint16_t rTime = 0;

    for (const char& lcfChar : pcfStr)
    {
        if (lcfChar == ':' || lcfChar == ' ')
        {
            uint16_t tSectInt = strtol(hSectStr.c_str(), 0, 0);
            uint16_t tMultiBy = 1;

            if (gParseHour)
            {
                if (tSectInt == 12) tSectInt = 0;
                tMultiBy = 60;
                gParseHour = false;
            }
            else
            {
                tSectInt = roundf(float(tSectInt)/15.0) * 15.0;
            }

            rTime += (tMultiBy * tSectInt);
            hSectStr.clear();
            gFrontDigit = true;
        }
        else if (lcfChar == 'P')
        {
            rTime += (60 * 12);
        }
        // else if is a digit from 0-9
        else if (cNum.find(lcfChar) != string::npos)
        {
            // Do not add 0 if it is the tenth digit place
            if (!(gFrontDigit && lcfChar == '0'))
            {
                hSectStr += lcfChar;
            }
            
            gFrontDigit = false;
        }
    }

    return rTime;
}


Weekday stoday(const string& pcfStr)
{
    Weekday rDay;
    
    if (pcfStr == "Monday") rDay = Weekday::MONDAY;
    else if (pcfStr == "Tuesday") rDay = Weekday::TUESDAY;
    else if (pcfStr == "Wednesday") rDay = Weekday::WEDNESDAY;
    else if (pcfStr == "Thursday") rDay = Weekday::THURSDAY;
    else if (pcfStr == "Friday") rDay = Weekday::FRIDAY;
    else rDay = Weekday::INVALID;
    
    return rDay;
}


void stoday(const string& pcfStr, vector<Weekday>* pnDays)
{
    if (pcfStr.find("Monday") != string::npos)
        pnDays->push_back(Weekday::MONDAY);
    if (pcfStr.find("Tuesday") != string::npos)
        pnDays->push_back(Weekday::TUESDAY);
    if (pcfStr.find("Wednesday") != string::npos)
        pnDays->push_back(Weekday::WEDNESDAY);
    if (pcfStr.find("Thursday") != string::npos)
        pnDays->push_back(Weekday::THURSDAY);
    if (pcfStr.find("Friday") != string::npos)
        pnDays->push_back(Weekday::FRIDAY);
}


string timetos(const uint16_t& pcfInt)
{
    uint16_t tHour = floor(pcfInt / 60),
             tMinute = pcfInt % 60;
    bool tAM = true;
    
    if (tHour == 0)
    {
        tHour = 12;
    }
    else if (tHour > 12)
    {
        tHour -= 12;
        tAM = false;
    }

    return cfill(to_string(tHour), '0', true, 2) + ":" +
        cfill(to_string(tMinute), '0', true, 2) + (tAM ? " AM" : " PM");
}


string daytos(const Weekday& pcfDay)
{
    switch (pcfDay)
    {
        case Weekday::MONDAY:
            return "Monday";
        case Weekday::TUESDAY:
            return "Tuesday";
        case Weekday::WEDNESDAY:
            return "Wednesday";
        case Weekday::THURSDAY:
            return "Thursday";
        case Weekday::FRIDAY:
            return "Friday";
    }

    return "INVALID";
}
