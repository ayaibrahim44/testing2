#ifndef SIM_MODE_H
#define SIM_MODE_H

#include "Action.h"

class SimMode : public Action
{
public:

	SimMode(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif