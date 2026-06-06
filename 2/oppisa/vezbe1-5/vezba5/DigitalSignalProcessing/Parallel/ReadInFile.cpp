#include "ReadInFile.h"

extern vector<int> in2FilterVector;

RetVal ReadInFile(string fileName)
{
	int x;
	ifstream inFile;

	inFile.open(_D_IN_FILE_NAME);
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	while (inFile >> x) {
		in2FilterVector.push_back(x);
	}

	size_t vel = in2FilterVector.size();
	cout << "SIZE = " << vel << endl;
	inFile.close();
	
    return RET_OK;
}
