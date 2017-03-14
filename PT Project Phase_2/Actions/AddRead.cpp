#include "AddRead.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

//constructor: set the ApplicationManager pointer inside this action
AddRead::AddRead(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddRead::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Add Read Statement: Click to add the statement");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();
	check = pManager->CheckArea(Position);
	if (!check)
	{
		pManager->GetOutput()->PrintMessage("Location is Unavailable");
		pManager->Lastmsg = "Location is Unavailable";
		return;
	}
	pOut->PrintMessage("Enter the variable name: ");
	Name = pIn->GetString(pOut);
	pOut->ClearStatusBar();
}


void AddRead::Execute()
{
	ReadActionParameters();
	if (!check)return;
	Read *pAssign = new Read(Position, Name);
	pManager->AddStatement(pAssign);
	pAssign->setID(pAssign->getIdset());
	pManager->Lastmsg = "Read statement added";
}