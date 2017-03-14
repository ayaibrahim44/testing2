
#include"AddEdit.h"

#include"..\Statements\Statement.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


#include <sstream>

AddEdit::AddEdit(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddEdit::ReadActionParameters()
{}

void AddEdit::Execute()
{
	ReadActionParameters();

	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	PRT = pManager->getSelectArray();

	for (int i = 0; i <pManager->GetSelectCount(); i++)
	{
		pOut->PrintMessage("Enter Edited statement");
		pManager->Lastmsg = "Enter Edited statement";
		PRT[i]->Edit(pOut, pIn);
		pManager->UpdateInterface();
	}
	Connector* c = pManager->getSelectedConnector();
	if (c != NULL)
	{
		Point p;
		pOut->PrintMessage("Choose new source statement");
		pIn->GetPointClicked(p);
		Statement* src = pManager->GetStatement(p);
		pOut->PrintMessage("Choose new destination statement");
		pIn->GetPointClicked(p);
		pOut->ClearStatusBar();
		Statement* dst = pManager->GetStatement(p);
		c->Edit(src, dst);
		pManager->Lastmsg = "Item edited";
	}
}
