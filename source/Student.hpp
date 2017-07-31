#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "Obligation.hpp"

class CSVReader;



class Student
{
public:
    Student(CSVReader* pnFile);
    virtual ~Student();

    std::string getName() const;
    std::string getEmail() const;
    std::string getInstrument() const;
    std::string getPrefEmail() const;
    std::string getPrefInstrument() const;

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

    std::vector<Obligation> iObligations;

    // Trims everything after and including the "@" off of an email
    void trimEmail(std::string& pfEmail);
};

#endif // STUDENT_HPP
