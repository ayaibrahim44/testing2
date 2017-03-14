
#include"Simulate.h"
#include "../ApplicationManager.h"

AddSimulate::AddSimulate(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddSimulate::ReadActionParameters()
{}

void AddSimulate::Execute()
{
	Statement* current = pManager->GetStartStat();
	current = current->getConnector()->getDstStat();
	pManager->GetOutput()->PrintMessage("Running..");
	while (current->getType() != "END")
	{
		current->Simulate(pManager->getVariables(), pManager->GetInput(), pManager->GetOutput());
		current = current->getConnector()->getDstStat();
	}
	pManager->Lastmsg = "End";
}
