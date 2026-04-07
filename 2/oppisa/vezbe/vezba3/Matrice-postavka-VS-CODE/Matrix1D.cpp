#include "Matrix1D.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Matrix1D::Matrix1D(int rows, int cols, int range) : rows(rows), cols(cols)
{
	// ZA URADITI:
	// Zauzeti memoriju za matricu dimenzija rows*cols
	
	// Matricu inicijalizovati nasumičnim vrednostima u opsegu [0, range)
}

void Matrix1D::print()
{
	// ZA URADITI:
	// Odštampati sadržaj matrice na ekran
}

void Matrix1D::process()
{
	// ZA URADITI:
	// Realizovati zadatu obradu nad matricom
}

Matrix1D::~Matrix1D()
{
	// ZA URADITI:
	// Osloboditi zauzetu memoriju
}
