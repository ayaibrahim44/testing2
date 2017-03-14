
#ifndef ADD_MOVE_H
#define ADD_MOVE_H

#include"Action.h"

class AddMove :public Action
{
	Point p;
public:
	AddMove(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif