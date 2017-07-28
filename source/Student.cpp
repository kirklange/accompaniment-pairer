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
}


Student::~Student()
{
}


void Student::printInfo() const
{
    cout << "Email:  " << iEmail << endl;
    cout << "Name:   " << iName << endl;
    cout << "Instru: " << iInstrument << endl;
    cout << "PrEml:  " << iPrefEmail << endl;
    cout << "PrIstr: " << iPrefInstrument << endl;
}


void Student::trimEmail(string& pfEmail)
{
    pfEmail = pfEmail.substr(0, pfEmail.find("@"));
}
