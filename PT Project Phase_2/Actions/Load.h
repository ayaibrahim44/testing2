
#ifndef ADD_LOAD_H
#define ADD_LOAD_H

#include"Action.h"

class AddLoad : public Action
{
public:
	AddLoad(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif