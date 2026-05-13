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
	currentToken = getNextToken();
	Q();
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
	if (errorFound == false)
	{
		if (currentToken.getType() == t)
		{
			cout << currentToken.getValue() << endl;
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

/*********************************************************************************
 Primer delimično urađenog sintaksnog analizatora za sledeću gramatiku:
 Q -> begin S L			S -> if E then S else S		L -> end		E -> id = num
						S -> print E				L -> S L
**********************************************************************************/
void SyntaxAnalysis::Q()
{
	if (errorFound == false)
	{
		eat(BEGIN);
		S();
		L();
	}
}


void SyntaxAnalysis::S()
{
	if (errorFound == false)
	{
		switch(currentToken.getType())
		{
			case IF:
			{
				eat(IF);
				E();
				eat(THEN);
				S();
				eat(ELSE);
				S();
				break;
			}
			case PRINT:
			{
				eat(PRINT);
				E();
				break;
			}
			default:
			{
				// error
				printSyntaxError(currentToken);
				errorFound = true;
				break;
			}
		}
	}
}


void SyntaxAnalysis::L()
{
	if (errorFound == false)
	{
	}
}


void SyntaxAnalysis::E()
{
	if (errorFound == false)
	{
		
	}
}
