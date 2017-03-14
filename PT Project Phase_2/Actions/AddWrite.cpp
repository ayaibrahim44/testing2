#include "AddWrite.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

//constructor: set the ApplicationManager pointer inside this action
AddWrite::AddWrite(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddWrite::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Add Write Statement: Click to add the statement");
	pIn->GetPointClicked(Position);

	check = pManager->CheckArea(Position);
	if (!check)
	{
		pManager->GetOutput()->PrintMessage("Location is Unavailable");
		pManager->Lastmsg = "Location is Unavailable";
		return;
	}

	pOut->ClearStatusBar();
	pOut->PrintMessage("Enter the variable name: ");
	Name = pIn->GetString(pOut);
	pOut->ClearStatusBar();
	pManager->Lastmsg = "Write statement added";
}


void AddWrite::Execute()
{
	ReadActionParameters();
	if (!check)return;
	Write *pAssign = new Write(Position, Name);
	pManager->AddStatement(pAssign);
	pAssign->setID(pAssign->getIdset());
}