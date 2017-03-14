
#ifndef ADD_SELECT_H
#define ADD_SELECT_H

#include"Action.h"

class Select :public Action
{
	Point p;
public:
	Select(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif