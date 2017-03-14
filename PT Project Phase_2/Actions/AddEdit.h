#ifndef ADD_EDIT_H
#define ADD_EDIT_H

#include "..\Statements\Statement.h"

#include"Action.h"

class AddEdit : public Action
{
private:
	Point Position;
	Statement**PRT;
	string Text;
public:
	AddEdit(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();

};


#endif