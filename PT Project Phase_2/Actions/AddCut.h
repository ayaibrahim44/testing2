
#ifndef ADD_CUT_H
#define ADD_CUT_H
#include "Action.h"

class Cut :public Action
{
private:
	Point Position;
	string Text;
public:
	Cut(ApplicationManager *pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};
#endif