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
        for (uint16_t j=i+1; j<stus.size(); j++)
        {
            // Compare students
        }

        stus[i]->printInfo();
        cout << endl;
    }

    return 0;
}
