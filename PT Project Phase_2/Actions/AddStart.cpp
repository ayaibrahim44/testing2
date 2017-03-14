#include "AddStart.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddStart::AddStart(ApplicationManager *pAppManager) :Action(pAppManager)
{}
void AddStart::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Start Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	check = pManager->CheckArea(Position);
	if (!check)
	{
		pManager->GetOutput()->PrintMessage("Location is Unavailable");
		pManager->Lastmsg = "Location is Unavailable";
		return;
	}
}


void AddStart::Execute()
{
	ReadActionParameters();
	if (!check)return;
	Start *pAssign = new Start(Position);
	pManager->AddStatement(pAssign);
	pAssign->setID(pAssign->getIdset());
	pManager->Lastmsg = "Start statement added";
}

