
#include "Load.h"
#include "../ApplicationManager.h"

AddLoad::AddLoad(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddLoad::ReadActionParameters()
{}

void AddLoad::Execute()
{
	pManager->Load();
}
