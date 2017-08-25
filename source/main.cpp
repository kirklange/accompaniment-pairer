#include "CSVReader.hpp"
#include "Student.hpp"
#include "util.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;



// This is a recursive function!
template<class T>
void pushAllPairs(const string& pcfObjName, vector<T*> *pnObjStack,
        vector<vector<pair<T*, T*> > > *pnPairSets)
{
    if (pnObjStack->size()%2 == 0 || pnObjStack->size() < 2)
    {
        if (pnPairSets->size() == 0)
        {
            vector<pair<T*, T*> > hBlankSet;
            pnPairSets->push_back(hBlankSet);
        }

        pair<T*, T*> hOnePair;
        hOnePair.first = pnObjStack->at(0);
        pnObjStack->erase(pnObjStack->begin());
        
        const uint16_t cStackSize = pnObjStack->size();
        for (uint16_t i=0; i<cStackSize; i++)
        {
            hOnePair.second = pnObjStack->at(i);
            pnObjStack->erase(pnObjStack->begin()+i);
            
            pnPairSets->back().push_back(hOnePair);

            if (cStackSize > 1)
            {
                pushAllPairs(pcfObjName, pnObjStack, pnPairSets);
            }
            else
            {
                vector<pair<T*, T*> > hBackCopy = pnPairSets->back();
                pnPairSets->push_back(hBackCopy);
            }

            pnPairSets->back().pop_back();
            
            pnObjStack->insert(pnObjStack->begin()+i, hOnePair.second);
        }

        pnObjStack->insert(pnObjStack->begin(), hOnePair.first);

        if (pnPairSets->back().size() == 0)
        {
            pnPairSets->erase(pnPairSets->end()-1);
        }
    }
    else
    {
        cout << "There is an invalid number of " + pcfObjName + "! Please "
            "modify the spreadsheet until there is an even number "
            "of at least two " + pcfObjName + "." << endl;
    }
}


void printAllPairs(const vector<vector<
        pair<Student*, Student*> > >& pcfPairSets)
{
    uint16_t i = 0;
    for (const auto& lcfPairSet : pcfPairSets)
    {
        cout << "SET " << i++ << endl;
        uint16_t score = 0;
        for (const auto& lcfOnePair : lcfPairSet)
        {
            cout << "    " << lcfOnePair.first->getName() << " & " <<
                lcfOnePair.second->getName();
            
            if (lcfOnePair.first->getPrefEmail() ==
                    lcfOnePair.second->getEmail())
            {
                cout << " [Pref'd Partner]";
            }
            if (lcfOnePair.first->getPrefInstrument() ==
                    lcfOnePair.second->getInstrument())
            {
                cout << " [Pref'd Instrument]";
            }

            cout << endl;
            score += lcfOnePair.first->scoreOverlap(lcfOnePair.second);
        }
        cout << "        SCORE SUM: " << score << endl;
    }
}


int main(int argc, char *argv[])
{
    CSVReader csvr("simple.csv");
    vector<Student*> stus;
    
    while(csvr.nextCell(CSVReader::Skip::ROW) &&
            csvr.nextCell(CSVReader::Skip::COLUMN))
    {
        stus.push_back(new Student(&csvr));
    }

    vector< vector<pair<Student*, Student*> > > stuPairSets;
    pushAllPairs("students", &stus, &stuPairSets);
    printAllPairs(stuPairSets);

    return 0;
}
