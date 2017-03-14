#include "AddSmplAssign.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddSmplAssign::AddSmplAssign(ApplicationManager *pAppManager) :Action(pAppManager)
{}


void AddSmplAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();


	pOut->PrintMessage("Simple Value Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();
	check = pManager->CheckArea(Position);
	if (!check)
	{
		pManager->GetOutput()->PrintMessage("Location is Unavailable");
		pManager->Lastmsg = "Location is Unavailable";
		return;
	}
	pOut->PrintMessage("Enter the variable name");
	LHS = pIn->GetString(pOut);


	pOut->PrintMessage("Enter a value");
	RHS = pIn->GetValue(pOut);

}

void AddSmplAssign::Execute()
{
	ReadActionParameters();
	if (!check)return;
	SmplAssign *pAssign = new SmplAssign(Position, LHS, RHS);
	pManager->AddStatement(pAssign);
	pAssign->setID(pAssign->getIdset());
	pManager->Lastmsg = "Simple assignment statement added";
}

