#include "ZoomOut.h"
#include "../ApplicationManager.h"

AddZoomOut::AddZoomOut(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddZoomOut::ReadActionParameters()
{}

void AddZoomOut::Execute()
{
	pManager->ZoomOut();
}
