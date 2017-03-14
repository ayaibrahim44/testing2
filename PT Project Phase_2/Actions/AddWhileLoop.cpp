#include "AddWhileLoop.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action

AddWhileLoop::AddWhileLoop(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddWhileLoop::ReadActionParameters()
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

void AddWhileLoop::Execute()
{
	ReadActionParameters();
	if (!check)return;
	if ((Variable2 == "" && Var2 != 0) || (Variable2 == "" && Var2 == 0))
	{
		Condition *pAssign = new SmpleWhileLoop(Position, Variable1, Var2, operation);
		pManager->AddStatement(pAssign);
		pAssign->setID(pAssign->getIdset());
	}
	else if (Variable2 != "" && Var2 == 0)
	{
		Condition *pAssign = new VarWhileLoop(Position, Variable1, Variable2, operation);
		pManager->AddStatement(pAssign);
		pAssign->setID(pAssign->getIdset());
	}
	pManager->Lastmsg = "While loop added";
}
