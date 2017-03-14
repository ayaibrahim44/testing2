#ifndef ADD_END_H
#define ADD_END_H

#include "Action.h"
#include "..\Statements\End.h"

class AddEnd : public Action
{
private:
	bool check;
	Point Position;	//Position where the user clicks to add the stat.
public:
	AddEnd(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif