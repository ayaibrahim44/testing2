
#include"AddConnector.h"
#include"../ApplicationManager.h"
#include"../GUI/Input.h"
#include"../GUI/Output.h"

//constructor: set the ApplicationManager pointer inside this action
AddConnector::AddConnector(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddConnector::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	pOut->PrintMessage("Add Connector: Choose source statement");
	pIn->GetPointClicked(Source);
	pOut->ClearStatusBar();

	pOut->PrintMessage("Add Connector: Choose destination statement");
	pIn->GetPointClicked(Destin);
	pOut->ClearStatusBar();
}

void AddConnector::Execute()
{
	ReadActionParameters(); //get source & destin points

	Statement* Sourcestat = pManager->GetStatement(Source);
	Statement* Deststat = pManager->GetStatement(Destin);
	if (Sourcestat != NULL && Deststat != NULL &&
		(Sourcestat->getConnector() == NULL || Sourcestat->getType() == "SMPL_IFCONDITION" || Sourcestat->getType() == "VAR_IFCONDITION"
		|| Sourcestat->getType() == "SMPL_WHILELOOP" || Sourcestat->getType() == "VAR_WHILELOOP"))
	{
		if (Sourcestat->getType() == "SMPL_IFCONDITION" || Sourcestat->getType() == "VAR_IFCONDITION"
			|| Sourcestat->getType() == "SMPL_WHILELOOP" || Sourcestat->getType() == "VAR_WHILELOOP")
		{
			if (Sourcestat->InFirstHalf(Source))
				Sourcestat->setBranch(true);
			else Sourcestat->setBranch(false);
		}
		Connector* connect = new Connector(Sourcestat, Deststat);
		connect->setStartPoint(Sourcestat->getOutlet());
		connect->setEndPoint(Deststat->getInlet());
		Sourcestat->setConnector(connect);
		Deststat->setToConnector(connect);
		pManager->appAddConnector(connect);
		pManager->Lastmsg = "Connector added";
	}
	pManager->Lastmsg = "";
}