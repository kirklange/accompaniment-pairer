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
    
    cout << "12:30 PM is " << stotime("12:30:00 PM") << endl;
    cout << "12:30 AM is " << stotime("12:30:00 AM") << endl;
    cout << " 2:00 PM is " << stotime("2:00 PM") << endl;
    cout << "11:15 AM is " << stotime("11:15 AM") << endl;
    cout << " 8:00 AM is " << stotime("8:00 AM") << endl;
    cout << " 8:06 AM is " << stotime("8:06 AM") << endl;
    cout << " 8:07 AM is " << stotime("8:07 AM") << endl;
    cout << " 8:08 AM is " << stotime("8:08 AM") << endl;
    cout << " 8:09 AM is " << stotime("8:09 AM") << endl;
    cout << " 8:15 AM is " << stotime("8:15 AM") << endl;

    return 0;
}
