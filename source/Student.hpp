#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "TimeSeg.hpp"

class CSVReader;



class Student
{
public:
    Student(CSVReader* pnFile);
    virtual ~Student();

    std::string getName() const;
    std::string getEmail() const;
    std::string getInstrument() const;
    TimeSeg getLesson() const;
    std::string getPrefEmail() const;
    std::string getPrefInstrument() const;
    const std::vector<TimeSeg>& getTimeSegs() const;

    void inverseTimeSegs();
    bool isInversed() const;

    uint16_t scoreOverlap(const Student* pnOther) const;
    bool canAttendLesson(const Student* pnOther) const;

    void printInfo() const;

private:
    // How early student signed up; lower is better
    const std::uint16_t icNumber;
    // A tally for initializing iNumber
    static std::uint16_t isTally;

    // Student's own info
    std::string iName, iEmail, iProfEmail, iInstrument;
    TimeSeg iLesson;
    // Student's accompanist preferences
    // iPrefInstrument does not matter if iInstrument is not "Piano". This is
    //   because non pianists will always (under this music department's
    //   circumstances) require a pianist accompanist.
    std::string iPrefEmail, iPrefInstrument;

    // When inversed, missing weekdays should count as free weekdays
    bool iInversed;

    std::vector<TimeSeg> iTimeSegs;

    // Trims everything after and including the "@" off of an email
    void trimEmail(std::string& pfEmail);
};

#endif // STUDENT_HPP
