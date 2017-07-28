#include <cstdint>
#include <string>

class CSVReader;



class Student
{
public:
    Student(CSVReader* pnFile);
    ~Student();

    void printInfo() const;

private:
    // How early student signed up; lower is better
    const std::uint16_t icNumber;
    // A tally for initializing iNumber
    static std::uint16_t isTally;

    // Student's own info
    std::string iName, iEmail, iInstrument;
    // Student's accompanist preferences
    // iPrefInstrument does not matter if iInstrument is not "Piano". This is
    //   because non pianists will always (under this music department's
    //   circumstances) require a pianist accompanist.
    std::string iPrefEmail, iPrefInstrument;

    // Trims everything after and including the "@" off of an email
    void trimEmail(std::string& pfEmail);
};
