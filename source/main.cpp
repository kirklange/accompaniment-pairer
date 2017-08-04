#include "CSVReader.hpp"
#include "Student.hpp"
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
        continue;
    }

    for (uint16_t i=0; i<stus.size(); i++)
    {
        stus[i]->printInfo();
        cout << endl;
        
        for (uint16_t j=i+1; j<stus.size(); j++)
        {
            for (const TimeSeg& lcfTimeSegI : stus[i]->getTimeSegs())
            {
                for (const TimeSeg& lcfTimeSegJ : stus[j]->getTimeSegs())
                {
                    lcfTimeSegI.printInfo();
                    cout << " AND" << endl;
                    lcfTimeSegJ.printInfo();
                    cout << " MATCH " <<
                        lcfTimeSegI.getOverlapTime(lcfTimeSegJ) <<
                        endl << endl;
                }
            }
        }

        cout << "~~~~~~~~~~" << endl;
    }

    return 0;
}
