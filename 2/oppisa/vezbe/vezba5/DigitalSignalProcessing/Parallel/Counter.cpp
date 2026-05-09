#include "Counter.h"
#include <iostream>

extern vector<int> clip2CounterVector;

//Funkcija za prebrojavanje nepromenjenih i odsečenih vrednosti
RetVal Counter(const vector<int>& beforeClipVector, const vector<int>& afterClipVector)
{
    if (beforeClipVector.size() != afterClipVector.size())
    {
        cout << "Vectors are not the same size." << endl;
        return RET_ERROR;
    }

    size_t size_v = afterClipVector.size();
    int unchangedValues = 0;
    int clippedValues = 0;

    // omp_set_num_threads(omp_get_max_threads());
    #pragma omp parallel for reduction(+:unchangedValues, clippedValues)
    for (int i = 0; i < size_v; i++)
    {
        if (beforeClipVector[i] == afterClipVector[i])
        {
            unchangedValues++;
        }
        else
        {
            clippedValues++;
        }
    }

    cout << "There are " << size_v << " elements." << endl;
    cout << unchangedValues << " of them are unchanged, and " << clippedValues << " are clipped." << endl;

    if ((unchangedValues + clippedValues) == size_v)
    {
        cout << "Looks all right." << endl;
    }
    else
    {
        cout << "Hold up - somethin' ain't right here..." << endl;
    }

    return RET_OK;
}