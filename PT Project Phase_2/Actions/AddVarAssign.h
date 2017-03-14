#ifndef ADD_VAR_ASSIGN_H
#define ADD_VAR_ASSIGN_H

#include "Action.h"
#include "..\Statements\VarAssign.h"


class AddVarAssign : public Action
{
private:
	bool check;
	Point Position;
	string LHS;
	string RHS;
public:
	AddVarAssign(ApplicationManager *pAppManager);


	virtual void ReadActionParameters();


	virtual void Execute();

};

#endif