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
            if (    (hOnePair.first->getInstrument()=="Piano" &&
                     hOnePair.first->canAttendLesson(pnObjStack->at(i)) &&
                     pnObjStack->at(i)->getInstrument()!="Piano") ||

                    (hOnePair.first->getInstrument()!="Piano" &&
                     pnObjStack->at(i)->getInstrument()=="Piano" &&
                     pnObjStack->at(i)->canAttendLesson(hOnePair.first)) ||

                    (hOnePair.first->getInstrument()=="Piano" &&
                     hOnePair.first->getPrefInstrument()==
                         pnObjStack->at(i)->getInstrument() &&
                     pnObjStack->at(i)->getInstrument()=="Piano")
                )
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


// Print all possible pairs (or only the best set) and display scores for
//   each set of pairs from the vector
void printPairSets(const bool& pcfPrintAllSets,
        vector<vector<pair<Student*, Student*> > > pStuPairSets)
{
    uint16_t i = 0, hTopScore = 0, hTopIndex = 0;
    for (const auto& lcfPairSet : pStuPairSets)
    {
        if (pcfPrintAllSets)
        {
            cout << "SET #" << i+1 << endl;
        }
        
        uint16_t score = 0;
        for (const auto& lcfOnePair : lcfPairSet)
        {
            if (pcfPrintAllSets)
            {
                cout << "    " << lcfOnePair.first->getName() << " & " <<
                    lcfOnePair.second->getName();
                
                if (lcfOnePair.first->getPrefEmail() ==
                        lcfOnePair.second->getEmail())
                {
                    if (lcfOnePair.second->getPrefEmail() ==
                            lcfOnePair.first->getEmail())
                    {
                        cout << " [Pref Partner MUTUAL]";
                    }
                    else
                    {
                        cout << " [Pref Partner]";
                    }
                }
                if (lcfOnePair.first->getPrefInstrument() ==
                        lcfOnePair.second->getInstrument())
                {
                    cout << " [Pref Instrument]";
                }

                cout << endl;
            }
            score += lcfOnePair.first->scoreOverlap(lcfOnePair.second);
        }
        if (pcfPrintAllSets)
        {
            cout << "        SCORE SUM: " << score << endl;
        }

        if (score > hTopScore)
        {
            hTopScore = score;
            hTopIndex = i;
        }

        i++;
    }

    cout << endl << "The best set is set #" << hTopIndex+1 << " with a score of "
        << hTopScore << endl;
}


// For each student, print compatability with every other student
void printAllForEach(const vector<Student*>& pcfStus)
{
    for (uint16_t i=0; i<pcfStus.size(); i++)
    {
        pcfStus[i]->printInfo();

        cout << endl << "Compatability w/ All Possible Partners:" << endl;
        for (uint16_t j=0; j<pcfStus.size(); j++)
        {
            if ( i!=j &&
                    ( ( pcfStus[i]->getInstrument()=="Piano" &&
                      pcfStus[j]->getInstrument()!="Piano" ) ||
                      ( pcfStus[i]->getInstrument()!="Piano" &&
                      pcfStus[j]->getInstrument()=="Piano" ) ||
                      ( pcfStus[i]->getPrefInstrument()==
                        pcfStus[j]->getInstrument() ) ) )
            {
                cout << "    w/ " <<
                    cfill(pcfStus[j]->getName() + ": ", ' ', false, 24) <<
                    pcfStus[i]->scoreOverlap(pcfStus[j]);

                // Pianists need to be able to make it to at least 20 minutes
                //   of their partner's lessons
                if (pcfStus[i]->getInstrument()=="Piano" &&
                        !pcfStus[i]->canAttendLesson(pcfStus[j]))
                {
                    cout << " [CANNOT ATTEND LESSON]";
                }
                
                if (pcfStus[i]->getPrefEmail()==pcfStus[j]->getEmail())
                {
                    cout << " [Pref Partner/Prof]";
                }

                if (pcfStus[i]->getPrefInstrument()==
                        pcfStus[j]->getInstrument())
                {
                    cout << " [Pref Instrument]";
                }

                cout << endl;
            }
        }

        for (uint16_t i=0; i<60; i++) { cout << "~"; } cout << endl;
    }
}


int main(int argc, char *argv[])
{
    CSVReader csvr("six_folk.csv");
    vector<Student*> stus;
    
    while(csvr.nextCell(CSVReader::Skip::ROW) &&
            csvr.nextCell(CSVReader::Skip::COLUMN))
    {
        stus.push_back(new Student(&csvr));
    }

    vector< vector<pair<Student*, Student*> > > stuPairSets;
    
    printAllForEach(stus);

    cout << endl << "ALL POSSIBLE SETS" << endl;
    pushAllPairs("students", &stus, &stuPairSets);
    printPairSets(true, stuPairSets);

    return 0;
}
