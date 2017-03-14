#include "AddCut.h"

#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <iostream>
using namespace std;
#include <sstream>


Cut::Cut(ApplicationManager *pAppManager) :Action(pAppManager)
{}
void Cut::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
}
void Cut::Execute()
{
	ReadActionParameters();
	Statement*selected_object = pManager->GetSelectedStatement();
	pManager->iscut = true;
	pManager->iscopy = false;
	if (selected_object != NULL)
    pManager->SetCutStatement(selected_object->Cut());
	pManager->Lastmsg = "Item cut";
}