#ifndef ADD_WRITE_H
#define ADD_WRITE_H

#include "Action.h"
#include "..\Statements\Write.h"

class AddWrite :public Action
{
	bool check;
	Point Position;
	string Name;
public:
	AddWrite(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif