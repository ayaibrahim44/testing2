#ifndef VALIDATE_H
#define VALIDATE_H

#include "Action.h"

class validation : public Action
{

public:
	validation(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif