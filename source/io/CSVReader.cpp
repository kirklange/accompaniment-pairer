#include "CSVReader.hpp"
#include <iostream>
using namespace std;



CSVReader::CSVReader(const string& pcfFileName)
{
    if (iFile.is_open())
    {
        iFile.close();
    }

    iFile.open(pcfFileName);
}


CSVReader::~CSVReader()
{
    iFile.close();
}


bool CSVReader::nextCell(string* pnCellStr, const CSVReader::Skip& pcfSkip)
{
    if (iFile.is_open())
    {
        char lChar;
        bool hitQuote = false;
        bool skipped = (pcfSkip == Skip::NONE);
        if (pnCellStr) pnCellStr->clear();
        
        while (iFile.get(lChar))
        {
            if (lChar == '"')
            {
                hitQuote = !hitQuote;
            }
            else if ((lChar == ',' || lChar == '\n') && !hitQuote)
            {
                if (!skipped)
                {
                    if ( (pcfSkip == Skip::COLUMN && lChar == ',') ||
                            (pcfSkip == Skip::ROW && lChar == '\n') )
                    {
                        skipped = true;
                        if (pnCellStr) pnCellStr->clear();
                        return true;
                    }
                }
                else
                {
                    return true;
                }
            }
            else
            {
                if (pnCellStr) *pnCellStr += lChar;
            }
        }
    }
    
    return false;
}
