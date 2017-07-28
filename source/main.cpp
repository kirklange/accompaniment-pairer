#include "io/CSVReader.hpp"
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    CSVReader csvr("simple.csv");
    string cell;
    
    while(csvr.nextCell(0, CSVReader::Skip::ROW) &&
            csvr.nextCell(0, CSVReader::Skip::COLUMN))
    {
        while (csvr.nextCell(&cell))
        {
            if (cell.size() == 0)
            {
                cell = "<EMPTY>";
            }
            else if (cell == "No")
            {
                cout << endl;
                break;
            }
            else if (cell != "Yes")
            {
                cout << cell << endl;
            }
        }
    }
    
    return 0;
}
