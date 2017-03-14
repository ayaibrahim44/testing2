#ifndef WATCH_H
#define WATCH_H

#include "Action.h"

class Watch : public Action
{
public:

	Watch(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif