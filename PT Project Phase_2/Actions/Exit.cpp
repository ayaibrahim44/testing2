#include "Exit.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


Exit::Exit(ApplicationManager *pAppManager) :Action(pAppManager)
{}
void Exit::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
}


void Exit::Execute()
{
	ReadActionParameters();
	pManager->~ApplicationManager();
}