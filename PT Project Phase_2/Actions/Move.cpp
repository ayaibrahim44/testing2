
#include"Move.h"
#include"../ApplicationManager.h"
#include"../GUI/Input.h"
#include"../GUI/Output.h"

#include<sstream>
using namespace std;

AddMove::AddMove(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddMove::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Move, click on new place");
	Statement** s = pManager->getSelectArray();
	if (s != NULL)
	{
		for (int i = 0; i<pManager->GetSelectCount(); i++)
		{
			pIn->GetPointClicked(p);
			s[i]->Move(p);
			pManager->Lastmsg = "Item moved";
			pManager->UpdateInterface();
		}
	}
	pOut->ClearStatusBar();
}

void AddMove::Execute()
{
	ReadActionParameters();
}