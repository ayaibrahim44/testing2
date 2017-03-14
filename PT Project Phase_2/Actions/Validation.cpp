#include "validation.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


validation::validation(ApplicationManager *pAppManager) :Action(pAppManager)
{}
void validation::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Click to validate the code");
	pOut->ClearStatusBar();
}


void validation::Execute()
{
	ReadActionParameters();
	pManager->Validate();

}