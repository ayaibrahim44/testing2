
#ifndef DSN_MODE_H
#define DSN_MODE_H

#include "Action.h"

class DsnMode : public Action
{
public:

	DsnMode(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif