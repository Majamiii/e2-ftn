#include <iostream>
#include <fstream>
#include <string>
#include "defines.h"
#include "ReadInFile.h"
#include "Filter.h"
#include "Clip.h"
#include "Counter.h"
#include "WriteOutFile.h"
#include "Globals.h"
#include <omp.h>

using namespace std;

int main(int argc, char* argv[])
{
    cout << endl << "Filterring started." << endl;

    double startTime = omp_get_wtime();

    double readInFileStartTime = omp_get_wtime();

    if (ReadInFile(_D_IN_FILE_NAME) == RET_ERROR)
    {
        cout << endl << "Error during reading input file." << endl;
        return RET_ERROR;
    }

    double readInFileEndTime = omp_get_wtime();
    cout << endl << "\tRead in file finished. Took: " << (readInFileEndTime - readInFileStartTime) * 1000 << "ms." << endl << endl;

    double FilterStartTime = omp_get_wtime();
    if (Filter() == RET_ERROR)
    {
        cout << endl << "Error in filter." << endl;
        return RET_ERROR;
    }

    double FilterEndTime = omp_get_wtime();
    cout << endl << "\tFilter finished. Took: " << (FilterEndTime - FilterStartTime) * 1000 << "ms." << endl << endl;

    double clipStartTime = omp_get_wtime();
    if (Clip(_D_CLIP_LOWER_VALUE, _D_CLIP_UPPER_VALUE) == RET_ERROR)
    {
        cout << endl << "Clip error." << endl;
        return RET_ERROR;
    }

    double clipEndTime = omp_get_wtime();
    cout << endl << "\tClipping finished. Took: " << (clipEndTime - clipStartTime) * 1000 << "ms." << endl << endl;

    double counterStartTime = omp_get_wtime();
    if (Counter(filter2ClipVector, clip2CounterVector) == RET_ERROR)
    {
        cout << endl << "Error in counter." << endl;
        return RET_ERROR;
    }

    double counterEndTime = omp_get_wtime();
    cout << endl << "\tCounting finished. Took: " << (counterEndTime - counterStartTime) * 1000 << "ms." << endl << endl;

    double writeOutFileStartTime = omp_get_wtime();
    if (WriteOutFile(_D_OUT_FILE_NAME) == RET_ERROR)
    {
        cout << endl << "Error during writing output file." << endl;
        return RET_ERROR;
    }

    double writeOutFileEndTime = omp_get_wtime();
    cout << endl << "\tWriting out file finished. Took: " << (writeOutFileEndTime - writeOutFileStartTime) * 1000 << "ms." << endl << endl;

    double endTime = omp_get_wtime();
    cout << endl << "Filterring finished. Took: " << (endTime - startTime) * 1000 << "ms." << endl << endl;

    return RET_OK;
}
