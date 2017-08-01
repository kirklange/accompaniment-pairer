#include "Student.hpp"
#include "CSVReader.hpp"
#include <iostream>
using namespace std;



uint16_t Student::isTally = 0;

Student::Student(CSVReader* pnFile) :
    icNumber(isTally++)
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
