#include "AddPaste.h"
#include "AddPaste.h"


#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <iostream>
using namespace std;
#include <sstream>
AddPaste::AddPaste(ApplicationManager *pAppManager) :Action(pAppManager)
{}
void AddPaste::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("click to paste a statement");
	pIn->GetPointClicked(Position);
}
void AddPaste::Execute()
{

	Statement*selected_object = pManager->GetSelectedStatement();
	if (selected_object != NULL)
	{
		ReadActionParameters();
		if (pManager->iscopy == true && pManager->iscut == false);
		{

			Statement*copied_object = pManager->GetCopiedStatement();
			copied_object->setposition(Position);
			pManager->Managerpaste(copied_object->Paste());
		}

		if (pManager->iscopy == false && pManager->iscut == true)
		{

			pManager->cutManager(selected_object);
			Statement*cut_object = pManager->GetCutStatement();
			cut_object->setposition(Position);
			pManager->Managerpaste(cut_object->Paste());
		}
	}
		else
		{
			Output *pOut = pManager->GetOutput();
			pManager->Lastmsg="You don't copy or cut anything ";

		}

	pManager->Lastmsg = "Item pasted";
}