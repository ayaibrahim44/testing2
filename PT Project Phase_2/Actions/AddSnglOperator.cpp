#include "AddSnglOperator.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action

AddSnglOperator::AddSnglOperator(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddSnglOperator::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Single operator Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	check = pManager->CheckArea(Position);
	if (check == false)
	{
		pOut->PrintMessage("Location is Unavailable");
		pManager->Lastmsg = "Location is Unavailable";
		return;
	}
	pOut->PrintMessage("Enter LHS");
	LHS = pIn->GetString(pOut);

	pOut->PrintMessage("Enter the expression");
	RHS = pIn->ReadExpression(pOut);

}

void AddSnglOperator::Execute()
{
	ReadActionParameters();
	if (!check)return;
	SnglOperator *pAssign = new SnglOperator(Position, LHS, RHS);
	pManager->AddStatement(pAssign);
	pAssign->setID(pAssign->getIdset());
	pManager->Lastmsg = "Single operator assignment statement added";
}
