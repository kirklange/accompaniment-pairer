#include "util.hpp"
#include <cmath>
#include <iostream>
using namespace std;



// string to time
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


// time to string
string timetos(const uint16_t& pcfInt)
{
    return "NOT YET";
}
