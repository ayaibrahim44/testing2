
#include"Select.h"
#include"../ApplicationManager.h"
#include"../GUI/Input.h"
#include"../GUI/Output.h"

Select::Select(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Select::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pIn->GetPointClicked(p);
}

void Select::Execute()
{
	Output *pOut = pManager->GetOutput();
	ReadActionParameters();
	Connector* selectedconn = pManager->GetConnector(p);
	if (selectedconn != NULL)
	{
		if (selectedconn->IsSelected())
		{
			selectedconn->setSelect(false);
			pManager->unselectCon(selectedconn);
		}
		else
		{
			selectedconn->setSelect(true);
			pManager->SetSelectedConnector(selectedconn);
			
		}
	}
	else
	{
		Statement* selectedStat = pManager->GetStatement(p);
		if (selectedStat != NULL)
		{
			if (selectedStat->IsSelected())
			{
				selectedStat->SetSelected(false);
				pManager->unselect(selectedStat);
			}
			else
			{
				selectedStat->SetSelected(true);
				pManager->SetSelectedStatement(selectedStat);
				pManager->Lastmsg = (selectedStat->PrintInfo());
			}
		}



	}
}

