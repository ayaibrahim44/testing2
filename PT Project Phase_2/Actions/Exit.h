#ifndef EXIT_H
#define EXIT_H
#include"Action.h"

class Exit :public Action
{
private:


public:
	Exit(ApplicationManager *pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};
#endif