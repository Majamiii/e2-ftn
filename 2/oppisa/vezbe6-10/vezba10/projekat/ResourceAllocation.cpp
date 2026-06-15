#include "ResourceAllocation.h"
#include "InterferenceGraph.h"
#include "Constants.h"
#include "Instruction.h"

Variables save;

int getColor(Variable* notColoredVariable, InterferenceGraph* ig) {

    // TO DO: Dobaviti promenljive sa kojima je u smetnji neobojena promeljiva sa stack-a,
    //        jer ne smeju dve promenljive u smetnji da dobiju isti registar (boju)
    //Napomena: smetnja je u InterferenceGraph-u oznacena kao __INTERFERENCE__

    int pos = notColoredVariable->pos;
    bool usedColors[4] = {0,0,0,0};

    for (int i = 0; i < ig->size; i++) {
        if (ig->values[pos][i] == __INTERFERENCE__) {
            for (auto it = ig->variables->begin(); it != ig->variables->end();++it) {
                Variable* var = *it;
                if (var->pos == i && var->assigment != __UNDEFINE__) {
                    usedColors[var->assigment] = 1;
                }
            }
        }
    }

    // TO DO: Pronaci boju koju mozemo dodeliti neobojenoj promenljivoj u skladu sa dobavljenom listom promenljivih u smetnji
    //Napomena: ukoliko ne postoji boja koju mozemo dodeliti promenljivoj vratiti 


    for (int color = reg0; color <= reg3; color++) {
        if (usedColors[color] == 0) {
            return color;
        }
    }

    return __UNDEFINE__;
}

bool doResourceAllocation(stack<Variable*>* simplificationStack, InterferenceGraph* ig) {

    Variable* currentVariable, * previusVariable;

    previusVariable = NULL;

    int counter = 0;

    while (simplificationStack->size() > 0) {

        currentVariable = simplificationStack->top();
        simplificationStack->pop();

        save.push_back(currentVariable);

        if (previusVariable == NULL) {
            // bojenje prvog cvora u stack-u
            currentVariable->assigment = (Regs)counter;
        }
        else {
            // dodeliti boju ako nije prvi cvor u stack-u
            int color = getColor(currentVariable, ig);
            if (color == __UNDEFINE__) {
                return false;
            }
            else {
                currentVariable->assigment = (Regs)color;
            }
        }

        previusVariable = currentVariable;
    }

    ig->variables = &save;

    return true;
}

/*
Реализовати брисање Т_MOVE инструкција у оквиру функције removeMove у датотеци
ResourceAllocation.cpp. Ова функција, након завршетка доделе ресурса, елиминише све инструкције које
представљају доделу регистра самом себи.
Instructions * removeMove(Instructions * instrs);
*/

Instructions* removeMove(Instructions* instrs) {
    Instructions* noMoveInstruction = new Instructions();

    for (auto instr : *instrs) {
        if (instr->type == T_MOVE) {
            if (instr->dst->assigment == instr->src1->assigment) {
                continue;
            }
            
        }
        else {
            noMoveInstruction->push_back(instr);
        }
    }

    return noMoveInstruction;
}