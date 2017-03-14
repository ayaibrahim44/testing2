#ifndef ADD_ZOOM_OUT_H
#define ADD_ZOOM_OUT_H

#include"Action.h"

class AddZoomOut : public Action
{
public:
	AddZoomOut(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif