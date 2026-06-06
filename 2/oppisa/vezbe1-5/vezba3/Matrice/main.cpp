#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Matrix1D.h"
#include "Matrix2D.h"
#include "MatrixVec.h"

using namespace std;

#define NUMBER_RANGE		10

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Niste uneli potrebne argumente za pokretanje programa!" << endl;
		cout << "Argumenti komandne linije treba da budu:" << endl;
		cout << "1. N dimenzija matrice" << endl;
		cout << "2. M dimenzija matrice" << endl;
		exit(-1);
	}

	// inicijalizacija generatora nasumičnih brojeva
	srand(unsigned int(time(NULL)));

	int rowNum = atoi(argv[1]);
	int colNum = atoi(argv[2]);

	// a)
	cout << endl << endl << "a) Matrix 1D representation" << endl;

	// ZA URADITI:
	// Napraviti objekat klase Matrix1D
	
	// Pozvati metodu print nad objektom
	
	// Pozvati metodu process nad objektom
	
	
	//b)
	cout << endl << endl << "b) Matrix 2D representation" << endl;

	// ZA URADITI:
	// Napraviti objekat klase Matrix2D
	
	// Pozvati metodu print nad objektom
	
	// Pozvati metodu process nad objektom
	
	//c)
	cout << endl << endl << "c) Matrix vector of vector representation" << endl;

	// ZA URADITI:
	// Napraviti objekat klase MatrixVec
	
	// Pozvati metodu print nad objektom
	
	// Pozvati metodu process nad objektom
	

	return 0;
}

