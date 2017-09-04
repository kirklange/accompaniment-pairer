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
void pushAllPairs(vector<T*> *pnObjStack,
        vector<vector<pair<T*, T*> > > *pnPairSets,
     // Set this to false, if you dare
        const bool& pcfFactorAttendLesson)
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
                        (hOnePair.first->canAttendLesson(pnObjStack->at(i)) ||
                         !pcfFactorAttendLesson) &&
                     pnObjStack->at(i)->getInstrument()!="Piano") ||

                    (hOnePair.first->getInstrument()!="Piano" &&
                     pnObjStack->at(i)->getInstrument()=="Piano" &&
                        (pnObjStack->at(i)->canAttendLesson(hOnePair.first) ||
                         !pcfFactorAttendLesson)) ||

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
                    pushAllPairs(pnObjStack, pnPairSets, pcfFactorAttendLesson);
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
        cout << "There is an invalid number of entries! Please modify the "
            "spreadsheet until it is an even number." << endl;
    }
}


// Print all possible pairs (or only the best set) and display scores for
//   each set of pairs from the vector
void printPairSets(vector<vector<pair<Student*, Student*> > > pStuPairSets,
        const bool& pcfPrintAllSets)
{
    if (pStuPairSets.size() > 0)
    {
        cout << "ALL POSSIBLE SETS" << endl;

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

        cout << endl << "The best set is set #" << hTopIndex+1 <<
            " with a score of " << hTopScore << endl;
    }
    else
    {
        cout << "Either there is a different number of pianists from "
            "non-pianists, or there is no possible way to pair everyone "
            "together such that every pianist can attend their collaborator's "
            "music lessons." << endl;
    }
}


// For each student, print compatability with every other student
void printAllForEach(const vector<Student*>& pcfStus,
        const bool& pcfPianistsOnly)
{
    for (uint16_t i=0; i<pcfStus.size(); i++)
    {
        if (pcfPianistsOnly && pcfStus[i]->getInstrument()=="Piano")
        {
            pcfStus[i]->printInfo();

            cout << endl << "List of All Possible Partners:" << endl;
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
                    cout << "    " <<
                        cfill(pcfStus[j]->getName() + " (" +
                                pcfStus[j]->getEmail() + ") ", ' ', false, 36)
                        /*<< pcfStus[i]->scoreOverlap(pcfStus[j])*/;

                    // Pianists need to be able to make it to at least 20
                    //   minutes of their partner's lessons
                    if (pcfStus[i]->getInstrument()=="Piano" &&
                        !pcfStus[i]->canAttendLesson(pcfStus[j]) &&
                        pcfStus[j]->getInstrument()!="Piano")
                    {
                        cout << " [CANNOT ATTEND LESSON]";
                    }
                    
                    if (pcfStus[i]->getPrefEmail()==pcfStus[j]->getEmail())
                    {
                        cout << " [Wants to work with this person!]";
                    }

                    if (pcfStus[i]->getPrefInstrument()==
                            pcfStus[j]->getInstrument())
                    {
                        cout << " [Preferred Instrument]";
                    }

                    cout << endl;
                }
            }

            for (uint16_t i=0; i<60; i++) { cout << "~"; } cout << endl;
        }
    }
}


int main(int argc, char *argv[])
{
    CSVReader csvr("real_11x2.csv");
    vector<Student*> stus;
    
    while(csvr.nextCell(CSVReader::Skip::ROW) &&
            csvr.nextCell(CSVReader::Skip::COLUMN))
    {
        stus.push_back(new Student(&csvr));
    }

    // For testing when there's not same amount of pianists as non-pianists
    if (false)
    {
        stus.pop_back();
        stus.pop_back();
    }

    vector< vector<pair<Student*, Student*> > > stuPairSets;
    
    printAllForEach(stus, true);

    /*
    cout << endl;
    pushAllPairs(&stus, &stuPairSets, true);
    printPairSets(stuPairSets, true);
    */

    return 0;
}
