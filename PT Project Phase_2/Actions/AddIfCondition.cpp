#include "AddIfCondition.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action

AddIfCondition::AddIfCondition(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddIfCondition::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Condition Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();
	check = pManager->CheckArea(Position);
	if (!check)
	{
		pManager->GetOutput()->PrintMessage("Location is Unavailable");
		pManager->Lastmsg = "Location is Unavailable";
		return;
	}
	pOut->PrintMessage("Enter the statement");
	pIn->ReadStat(pOut, Variable1, operation, Variable2, Var2);

}

void AddIfCondition::Execute()
{
	ReadActionParameters();
	if (!check)return;
	if (Variable2 == "" && Var2 != 0 || (Variable2 == "" && Var2 == 0))
	{
		Condition *pAssign = new SmpleIfCondition(Position, Variable1, Var2, operation);
		pManager->AddStatement(pAssign);
		pAssign->setID(pAssign->getIdset());
	}
	else if (Variable2 != "" && Var2 == 0)
	{
		Condition *pAssign = new VarIfCondition(Position, Variable1, Variable2, operation);
		pManager->AddStatement(pAssign);
		pAssign->setID(pAssign->getIdset());
	}
	pManager->Lastmsg = "If conditional statement added";
}
