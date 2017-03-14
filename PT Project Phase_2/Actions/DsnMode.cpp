
#include "DsnMode.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

DsnMode::DsnMode(ApplicationManager *pAppManager) :
Action(pAppManager) {}

void DsnMode::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	//pOut->PrintMessage("Switch to design mode");
	pManager->Lastmsg = "Switch to design mode";
	pOut->CreateDesignToolBar();
}

void DsnMode::Execute()
{
	ReadActionParameters();
}
