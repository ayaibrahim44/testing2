
#ifndef SIMULATE_STEP_H
#define SIMULATE_STEP_H

#include "Action.h"

class AddSimulate : public Action
{
public:

	AddSimulate(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif