

#ifndef ADD_SAVE_H
#define ADD_SAVE_H

#include"Action.h"

class AddSave : public Action
{
public:
	AddSave(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif