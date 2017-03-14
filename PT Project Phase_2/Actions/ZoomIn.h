#ifndef ADD_ZOOM_IN_H
#define ADD_ZOOM_IN_H

#include"Action.h"

class AddZoomIn : public Action
{
public:
	AddZoomIn(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif