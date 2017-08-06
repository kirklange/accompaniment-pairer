#include "CSVReader.hpp"
#include "Student.hpp"
#include "util.hpp"
#include <iostream>
#include <vector>
using namespace std;



int main(int argc, char *argv[])
{
    CSVReader csvr("simple.csv");
    vector<Student*> stus;
    
    while(csvr.nextCell(CSVReader::Skip::ROW) &&
            csvr.nextCell(CSVReader::Skip::COLUMN))
    {
        stus.push_back(new Student(&csvr));
        // Makes it so that students' non-free time turns into free time
        stus[stus.size()-1]->inverseTimeSegs();
    }

    for (uint16_t i=0; i<stus.size(); i++)
    {
        stus[i]->printInfo();

        cout << endl << "Schedule Compatability" << endl;
        // "j=i+1" would output more space efficient stuff but by having info
        //   for each student at every student the data is easier to reference
        for (uint16_t j=0; j<stus.size(); j++)
        {
            // Do not compare with self of course!
            if (j != i)
            {
                uint16_t overlapScore = 0;

                for (uint8_t lDay=0; lDay!=Weekday::INVALID; lDay++ )
                {
                    for (uint16_t lTime=0; lTime<1440; lTime+=15)
                    {
                        if ( stuAvailAt(lTime, (Weekday) lDay, *stus[i]) &&
                                stuAvailAt(lTime, (Weekday) lDay, *stus[j]) )
                        {
                            overlapScore += 15;
                        }
                    }
                }
                
                cout << "    w/ " <<
                    cfill(stus[j]->getName() + ": ", ' ', false, 24) <<
                    overlapScore << " / 7200" << endl;
            }
        }

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }

    cin.ignore();

    return 0;
}
