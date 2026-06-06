#include "Clip.h"

extern vector<int> filter2ClipVector;
extern vector<int> clip2CounterVector;

// Funkcija za odsecanje viska vrednosti
RetVal Clip(int lowerValue, int upperValue)
{
	// odsecanje svake vrednosti
	size_t size_v = filter2ClipVector.size();
	int i;


	#pragma omp parallel for
	for (i = 0; i < size_v; i++) {
		int data = filter2ClipVector[i];
		if (data<lowerValue)
		{
			data = lowerValue;
		}
		else if (data>upperValue)
		{
			data = upperValue;
		}
		clip2CounterVector[i] = data;
		//clip2CounterVector.push_back(data);
	}
    return RET_OK;
}
