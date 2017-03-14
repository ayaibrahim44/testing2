#ifndef ADD_COPY_H
#define ADD_COPY_H
#include "Action.h"

class Copy :public Action
{
private:
	Point Position;
public:
	Copy(ApplicationManager *pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();
};
#endif