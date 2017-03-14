#ifndef ADD_SNGL_OPER_H
#define ADD_SNGL_OPER_H

#include "Action.h"
#include "..\Statements\SnglOperator.h"

class AddSnglOperator : public Action
{
private:
	bool check;
	Point Position;	
	string LHS;
	string RHS;
public:
	AddSnglOperator(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};

#endif