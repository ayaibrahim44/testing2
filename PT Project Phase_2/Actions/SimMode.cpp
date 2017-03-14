
#include "SimMode.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

SimMode::SimMode(ApplicationManager *pAppManager) :
Action(pAppManager) {}

void SimMode::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Switch to simulation mode");
	pManager->Lastmsg = "Simulation mode";
	pOut->CreateSimulationToolBar();
}

void SimMode::Execute()
{
	ReadActionParameters();
}
