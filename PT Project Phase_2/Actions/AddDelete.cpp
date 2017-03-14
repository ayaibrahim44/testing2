#include "AddDelete.h"
#include"..\Statements\Statement.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

Delete::Delete(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Delete::ReadActionParameters()
{
	Pointer = pManager->getSelectArray();
	con = pManager->getSelectedConnArray();
}
void Delete::Execute()
{
	ReadActionParameters();
	if (Pointer[0] != NULL || con[0] != NULL)
	{

		for (int i = 0; i < pManager->GetSelectCount(); i++)
		{
			pManager->DeleteStatement(Pointer[i]);
		}
		for (int i = 0; i < pManager->getCSelectCount(); i++)
		{
			pManager->DeleteConnector(con[i]);
		}
		pManager->Lastmsg = "Item deleted";
	}
	else
		pManager->Lastmsg = "select statement";
	
	
}