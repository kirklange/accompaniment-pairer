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
    string cell;
    
    while(csvr.nextCell(CSVReader::Skip::ROW) &&
            csvr.nextCell(CSVReader::Skip::COLUMN))
    {
        stus.push_back(new Student(&csvr));
        continue;
    }

    for (const Student* lcnStu : stus)
    {
        lcnStu->printInfo();
        cout << endl;
    }

    return 0;
}
