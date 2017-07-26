#include "csv/CSVR.hpp"
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    CSVR csvr("simple.csv");
    string cell;
    while (csvr.nextCell(&cell))
    {
        if (cell.size() == 0) cell = "<EMPTY>";
        if (cell == "No")
        {
            csvr.nextCell(0, CSVR::Skip::ROW);
        }
        cout << cell << endl;
    }
    
    return 0;
}
