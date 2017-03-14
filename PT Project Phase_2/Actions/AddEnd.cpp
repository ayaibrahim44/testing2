#include "AddEnd.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddEnd::AddEnd(ApplicationManager *pAppManager) :Action(pAppManager)
{}
void AddEnd::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("End Statement: Click to add the statement");
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


void AddEnd::Execute()
{
	ReadActionParameters();
	if (!check)return;
	End *pAssign = new End(Position);
	pManager->AddStatement(pAssign);
	pAssign->setID(pAssign->getIdset());
	pManager->Lastmsg = "End statement added";
}