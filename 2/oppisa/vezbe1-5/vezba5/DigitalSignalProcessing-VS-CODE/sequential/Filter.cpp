#include "Filter.h"

extern vector<int> in2FilterVector;
extern vector<int> filter2ClipVector;

using namespace std;
//Funkcija za filtriranje ulaznih podataka
RetVal Filter()
{
	int i;
	int Arg;
	size_t size_vec = in2FilterVector.size();
	//filter2ClipVector.resize(size_vec - 2);

	for (i = 1; i < size_vec - 1; ++i) {
		float a = static_cast<float>(in2FilterVector[i - 1]);
		float b = static_cast<float>(in2FilterVector[i]);
		float c = static_cast<float>(in2FilterVector[i + 1]);
		float avg = (a + b + c) / 3.0f;
		Arg = static_cast<int>(sqrt((pow(a - avg, 2) + pow(b - avg, 2) + pow(c - avg, 2)) / 3.0f));
		filter2ClipVector.push_back(Arg);
	}

	return RET_OK;
}
