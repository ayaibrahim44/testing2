#include "AddVarAssign.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;


AddVarAssign::AddVarAssign(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddVarAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("variable Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	check = pManager->CheckArea(Position);
	if (!check)
	{
		pManager->GetOutput()->PrintMessage("Location is Unavailable");
		pManager->Lastmsg = "Location is Unavailable";
		return;
	}

	pOut->PrintMessage("Enter the first variable");
	LHS = pIn->GetString(pOut);

	pOut->PrintMessage("Enter the second variable");
	RHS = pIn->GetString(pOut);
}

void AddVarAssign::Execute()
{
	ReadActionParameters();
	if (!check)return;

	VarAssign *pAssign = new VarAssign(Position,LHS,RHS);

	pManager->AddStatement(pAssign);
	pAssign->setID(pAssign->getIdset());
	pManager->Lastmsg = "Variable assignment statement added";
}
