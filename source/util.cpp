#include "util.hpp"
using namespace std;



// string to time
// SOME OF THE ASSUMPTIONS
//   1) First section is hour
//   2) Seconds section (if there is one) is always zero
//   3) Format is 12 hour AM/PM time
uint16_t stotime(const string& pcfStr)
{
    const string cNum = "0123456789";
    string hSectStr;
    bool gParseHour = true;
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

            rTime += (tMultiBy * tSectInt);
            hSectStr.clear();
        }
        else if (lcfChar == 'P')
        {
            rTime += (60 * 12);
        }
        // else if is a digit from 0-9
        else if (cNum.find(lcfChar) != string::npos)
        {
            hSectStr += lcfChar;
        }
    }

    return rTime;
}


// time to string
string timetos(const uint16_t& pcfInt)
{
    return "NOT YET";
}
