#include "Munch.h"
#include "Instruction.h"
#include "Registers.h"

#include <cassert>
#include <string>
#include <sstream>

using namespace std;


static InstructionList selectedInstructions;

/*
* Use this function to translate integer value to string
*/
string toString(int value)
{
	string retVal = "";
	stringstream s;
	s << value;
	s >> retVal;
	return retVal;
}

/*
* Add the instruction to the list of selected instructions
*/
void emit(Instruction* instr)
{
	selectedInstructions.push_back(instr);
}


InstructionList& getInstructionList()
{
	return selectedInstructions;
}


void munchStm(Statement* statement)
{
	switch (statement->getType())
	{
		case Statement::MOVE_STM:
		{
			S_Move* moveStm = static_cast<S_Move*>(statement);

			Expression* destExp = moveStm->getLeftExp();
			Expression* srcExp = moveStm->getRightExp();

			// If the destination expression is memory access,
			// the MOVE statement represents store to memory.
			if (destExp->getType() == Expression::MEM_EXP)
			{
				// TODO (additional task): implement sw instruction.
				// Goal: translate MOVE(MEM(...), EXP) into sw instruction.
				//
				// Required cases:
				// 1) MOVE(MEM(BINOP(PLUS, EXP, CONST)), EXP) -> sw `s,const(`s)
				// 2) MOVE(MEM(BINOP(PLUS, CONST, EXP)), EXP) -> sw `s,const(`s)
				// 3) MOVE(MEM(CONST), EXP)                   -> sw `s,const($zero)
				// 4) MOVE(MEM(EXP), EXP)                     -> sw `s,0(`s)
				//
				// Hints:
				// - srcExp is the value that should be stored.
				// - The expression inside MEM(...) represents the memory address.
				// - Use munchExp(...) to evaluate expressions that must be placed in registers.
				// - Fill the source register list in the same order as `s appears in instructionString.
				// - Call emit(instr) after creating and filling the instruction.

				assert(0);
			}
			else
			{
				assert(0);
			}
		}
		break;


		case Statement::SEQ_STM:
		{
			S_Seq* stmSeq = static_cast<S_Seq*>(statement);

			Statement* left = stmSeq->getLeftStm();
			Statement* right = stmSeq->getRightStm();

			munchStm(left);
			munchStm(right);
		}
		break;


		case Statement::EXP_STM:
		{
			S_Exp* stmExp = static_cast<S_Exp*>(statement);
			Expression* expression = stmExp->getExp();

			munchExp(expression);
		}
		break;


		default:
			assert(0);
	}
}


Reg munchExp(Expression* expression)
{
	switch (expression->getType())
	{
		case Expression::MEM_EXP:
		{
			// TODO: implement lw instruction.
			// Goal: translate MEM(...) expression into lw instruction.
			//
			// Required cases:
			// 1) MEM(BINOP(PLUS, EXP, CONST)) -> lw `d,const(`s)
			// 2) MEM(BINOP(PLUS, CONST, EXP)) -> lw `d,const(`s)
			// 3) MEM(CONST)                   -> lw `d,const($zero)
			// 4) MEM(EXP)                     -> lw `d,0(`s)
			//
			// Suggested steps:
			// - Extract the expression inside MEM(...).
			// - Detect whether the address has the form base + constant.
			// - Build instructionString.
			// - Create a new destination register.
			// - Add destination register to dst list.
			// - If the instruction has a base register, evaluate it using munchExp(...)
			//   and add it to src list.
			// - Emit the instruction and return the destination register.

			assert(0);
			return -1;
		}

		case Expression::BINOP_EXP:
		{
			E_Binop* binopExp = static_cast<E_Binop*>(expression);

			Expression* leftExp = binopExp->getLeftExp();
			Expression* rightExp = binopExp->getRightExp();

			string instructionString;
			Expression* srcExp1 = nullptr;
			Expression* srcExp2 = nullptr;

			if (binopExp->getOperType() == E_Binop::PLUS_OP)
			{
				if (rightExp->getType() == Expression::CONST_EXP)
				{
					// TODO: implement BINOP(PLUS, EXP, CONST) -> addi.
					// - Extract constant value from rightExp.
					// - Build instructionString: addi `d,`s,const
					// - Set srcExp1 to the expression that should be evaluated into source register.
					E_Const* constExp = static_cast<E_Const*>(rightExp);
					instructionString = "addi `d,`s," + toString(constExp->getValue());
					srcExp1 = leftExp;

				}
				else if (leftExp->getType() == Expression::CONST_EXP)
				{
					// TODO: implement BINOP(PLUS, CONST, EXP) -> addi.
					// - Extract constant value from leftExp.
					// - Build instructionString: addi `d,`s,const
					// - Set srcExp1 to the expression that should be evaluated into source register.
					E_Const* constExp = static_cast<E_Const*>(leftExp);
					instructionString = "addi `d,`s," + toString(constExp->getValue());
					srcExp1 = rightExp;

				}
				else
				{
					// BINOP(PLUS, EXP, EXP) -> add
					instructionString = "add `d,`s,`s";
					srcExp1 = leftExp;
					srcExp2 = rightExp;
				}
			}
			else if (binopExp->getOperType() == E_Binop::MINUS_OP)
			{
				// TODO: implement BINOP(MINUS, EXP, EXP) -> sub.
				// - Build instructionString: sub `d,`s,`s
				// - Set srcExp1 to leftExp.
				// - Set srcExp2 to rightExp.

				instructionString = "sub `d,`s,`s";
				srcExp1 = leftExp;
				srcExp2 = rightExp;

			}
			else
			{
				assert(0);
			}

			// Common part for add/addi/sub.
			// After TODO blocks are implemented, instructionString and srcExp1 must be set.
			
			Reg dstReg = getNewReg();

			Instruction* instr = new Instruction(instructionString);

			if (srcExp1 != nullptr)
			{
				instr->getDst().push_back(dstReg);

				// The first source expression is always needed.
				Reg srcReg1 = munchExp(srcExp1);
				instr->getSrc().push_back(srcReg1);
			}
			// The second source expression is needed only for add/sub.
			if (srcExp2 != nullptr)
			{
				Reg srcReg2 = munchExp(srcExp2);
				instr->getSrc().push_back(srcReg2);
			}

			emit(instr);

			return dstReg;
		}

		case Expression::REG_EXP:
		{
			E_Reg* regExp = static_cast<E_Reg*>(expression);
			return regExp->getRegId();
		}

		case Expression::CONST_EXP:
		{
			E_Const* constExp = static_cast<E_Const*>(expression);

			string instructionString = "li `d, " + toString(constExp->getValue());

			Reg dstReg = getNewReg();

			Instruction* instr = new Instruction(instructionString);
			instr->getDst().push_back(dstReg);

			emit(instr);

			return dstReg;
		}

		case Expression::ESEQ_EXP:
		{
			E_Eseq* eseqExp = static_cast<E_Eseq*>(expression);

			Expression* eseqLeft = eseqExp->getLeftExp();
			Statement* eseqRight = eseqExp->getRightStm();

			Reg dstReg = munchExp(eseqLeft);
			munchStm(eseqRight);

			return dstReg;
		}

		default:
			assert(0);
			return -1;
	}

	assert(0);
	return -1;
}
