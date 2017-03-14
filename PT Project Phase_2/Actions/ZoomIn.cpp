
#include "ZoomIn.h"
#include "../ApplicationManager.h"

AddZoomIn::AddZoomIn(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddZoomIn::ReadActionParameters()
{}

void AddZoomIn::Execute()
{
	pManager->ZoomIn();
}
