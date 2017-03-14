
#include "Save.h"
#include "../ApplicationManager.h"

AddSave::AddSave(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddSave::ReadActionParameters()
{}

void AddSave::Execute()
{
	pManager->Save();
}
