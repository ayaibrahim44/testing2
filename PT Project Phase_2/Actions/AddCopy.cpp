#include "AddCopy.h"
#include "AddCopy.h"

#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <iostream>
using namespace std;
#include <sstream>


Copy::Copy(ApplicationManager *pAppManager) :Action(pAppManager)
{}
void Copy::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

}
void Copy::Execute()
{

	ReadActionParameters();
	Statement*selected_object = pManager->GetSelectedStatement();
	pManager->iscopy = true;
	pManager->iscut = false;
	if (selected_object != NULL)
	pManager->SetCopiedStatement(selected_object->Copy());
	pManager->unselect(selected_object);
	pManager->Lastmsg = "Item copied";
}