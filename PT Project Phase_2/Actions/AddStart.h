#ifndef ADD_START_H
#define ADD_START_H

#include "Action.h"
#include "..\Statements\Start.h"

class AddStart : public Action
{
private:
	bool check;
	Point Position;	//Position where the user clicks to add the stat.
public:
	AddStart(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif