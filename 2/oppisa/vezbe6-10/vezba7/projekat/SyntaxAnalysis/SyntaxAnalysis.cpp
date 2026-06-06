#include <iostream>
#include <iomanip>

#include "SyntaxAnalysis.h"

using namespace std;


SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lex)
	: lexicalAnalysis(lex), errorFound(false), tokenIterator(lexicalAnalysis.getTokenList().begin())
{
}


bool SyntaxAnalysis::Do()
{
	tokenIterator = lexicalAnalysis.getTokenList().begin();
	currentToken = getNextToken();
	
	//TO DO: Call function for the starting non-terminal symbol

	Q();

	if (!errorFound)
		cout << "Syntax OK" << endl;

	return !errorFound;
}


void SyntaxAnalysis::printSyntaxError(Token token)
{
	cout << "Syntax error! Token: " << token.getValue() << " unexpected" << endl;
}


void SyntaxAnalysis::printTokenInfo(Token token)
{
	cout << setw(20) << left << token.tokenTypeToString();
	cout << setw(25) << right << token.getValue() << endl;
}


void SyntaxAnalysis::eat(TokenType t)
{
	if (errorFound) return;
	if (errorFound == false)
	{
		if (currentToken.getType() == t)
		{
			printTokenInfo(currentToken);
			currentToken = getNextToken();
		}
		else
		{
			printSyntaxError(currentToken);
			errorFound = true;
		}
	}
}


Token SyntaxAnalysis::getNextToken()
{
	if (tokenIterator == lexicalAnalysis.getTokenList().end())
		throw runtime_error("End of input file reached");
	return *tokenIterator++;
}


void SyntaxAnalysis::Q()
{
	if (errorFound) return;
	eat(BEGIN);
	L();
}


void SyntaxAnalysis::S()
{
	if (errorFound) return;
	if (currentToken.getType() == IF) {
		eat(IF);
		C();
		eat(THEN);
		K();

		if (!errorFound && currentToken.getType() == ELSE) {
			eat(ELSE);
			K();
		}
	}
	else {
		K();
	}
}


void SyntaxAnalysis::L()
{
	if (errorFound) return;
	if (currentToken.getType() == END) {
		eat(END);
	}
	else {
		S();
		L();
	}
}


void SyntaxAnalysis::E()
{
	eat(ID);
	eat(EQ);
	R();
}


void SyntaxAnalysis::K()
{
	if (currentToken.getType() == BEGIN) {
		eat(BEGIN);
		L();
	}
	else if (currentToken.getType() == ID) {
		E();
		eat(SEMI);
	}
	else {
		printSyntaxError(currentToken);
		errorFound = true;
	}
}


void SyntaxAnalysis::C()
{
	R();
	eat(EQEQ);
	R();
}


void SyntaxAnalysis::R()
{
	switch (currentToken.getType()){
		case ID:   eat(ID);
			break;
		case NUM:  eat(NUM);
			break;
		case REAL: eat(REAL);
			break;
		default:
			printSyntaxError(currentToken);
			errorFound = true;
	}
}