#include "Watch.h"
#include "../ApplicationManager.h"

Watch::Watch(ApplicationManager *pAppManager) :
Action(pAppManager) {}

void Watch::ReadActionParameters()
{

}

void Watch::Execute()
{
	Input* pIn = pManager->GetInput();
	Statement* current = pManager->GetStartStat();
	Output* pOut = pManager->GetOutput();
	do
	{
		current->Simulate(pManager->getVariables(), pIn, pManager->GetOutput());
		current->watch(pManager->getVariables(), pOut);
		if (current->getConnector() == NULL)
		{
			pManager->getVariables().clear();
			break;
		}
		current = current->getConnector()->getDstStat();
	} while (pIn->GetUserAction() == STEP);
}

