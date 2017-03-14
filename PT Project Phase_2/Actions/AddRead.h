#ifndef ADD_READ_H
#define ADD_READ_H

#include "Action.h"
#include "..\Statements\Read.h"

class AddRead :public Action
{
	bool check;
	Point Position;
	string Name;
public:
	AddRead(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif