#include "ApplicationManager.h"
#include "Actions\AddStart.h"
#include "Actions\AddEnd.h"
#include "Actions\AddSmplAssign.h"
#include "Actions\Validation.h"
#include "Actions\AddVarAssign.h"
#include "Actions\AddSnglOperator.h"
#include "Actions\AddIfCondition.h"
#include "Actions\AddWhileLoop.h"
#include "Actions\AddRead.h"
#include "Actions\AddWrite.h"
#include "Actions\AddEdit.h"
#include"Actions\AddDelete.h"
#include"Actions\AddComment.h"
#include "Actions\Move.h"
#include "Actions\Select.h"
#include "Actions\AddConnector.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Actions\Save.h"
#include "Actions\Load.h"
#include "Actions\AddGenerateCode.h"
#include "Actions\ZoomIn.h"
#include "Actions\ZoomOut.h"
#include "Actions\DsnMode.h"
#include "Actions\SimMode.h"
#include "Actions\Simulate.h"
#include "Actions\Watch.h"
#include"Actions\AddCopy.h"
#include"Actions\AddCut.h"
#include"Actions\AddPaste.h"
#include"Actions\Exit.h"
using namespace std;

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	selectCount = 0;
	CselectCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	SelectedCo = 0;

	ZoomedIn = ZoomedOut = false;
	
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
		selectedarray[i] = NULL;
		selectedConnectors[i] = NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;

	switch (ActType)
	{
		case SIM_MODE:
		pAct = new SimMode(this);
		break;

		case DSN_MODE:
		pAct = new DsnMode(this);
		break;

		case ADD_START:
		pAct = new AddStart(this);
		break;

		case ADD_END:
		pAct = new AddEnd(this);
		break;

		case ADD_READ:
		pAct = new AddRead(this);
		break;

		case ADD_WRITE:
		pAct = new AddWrite(this);
		break;

		case ADD_SMPL_ASSIGN:
		pAct = new AddSmplAssign(this);
		break;

		case ADD_VAR_ASSIGN:
		pAct = new AddVarAssign(this);
		break;

		case ADD_SNGL_OPERAT:
		pAct = new AddSnglOperator(this);
		break;

		case ADD_IF_CONDITION: 
		pAct = new AddIfCondition(this);
		break;

		case ADD_WHILE_LOOP:
		pAct = new AddWhileLoop(this);
		break;

		case ADD_CONNECTOR:
		pAct = new AddConnector(this);
		break;

		case SELECT:
		pAct = new Select(this);
		break;
	
		case EDIT_STAT:
		pAct = new AddEdit(this);
		break;

		case DEL:
		pAct = new Delete(this);
		break;

		case ZOOM_IN:
		pAct = new AddZoomIn(this);
		break;

		case ZOOM_OUT:
		pAct = new AddZoomOut(this);
		break;

		case COPY:
		pAct = new Copy(this);
		break;

		case CUT:
		pAct = new Cut(this);
		break;
		
		case PASTE:
		pAct = new AddPaste(this);
		break;

		case MOVE:
		pAct = new AddMove(this);
		break;

		case COMMENT:
		pAct = new Comment(this);
		break;

		case SAVE:
		pAct = new AddSave(this);
		break;

		case LOAD:
		pAct = new AddLoad(this);
		break;

		case CODE:
		pAct = new AddGenerateCode(this);
		break;

		case RUN:
		pAct = new AddSimulate(this);
		break;

		case STEP:
		pAct = new Watch(this);
		break;

		case VALIDATE:
		pAct = new validation(this);
		break;

		case EXIT:
		break;

		case STATUS:
		return;

	}
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}


bool ApplicationManager::CheckArea(Point p) const
{
	if (p.y >= UI.HorTlBrWdth + 50 && p.y < UI.height - UI.StBrWdth - 50 && p.x >= 0 && p.x <= UI.width - UI.VerTlBrWdth - 50);
	else return false;

	for (int i = 0; i < StatCount; i++)
	{
		bool check = StatList[i]->InArea(p);
		if (check == true) return false;
	}
	return true;
}


//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//
//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
}
void ApplicationManager::DeleteStatement(Statement*DStat)
{
	int count;
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i] == DStat)
		{
			Statement*S = DStat;
			
			if (StatList[i]->getType() == "SMPL_IFCONDITION" || StatList[i]->getType() == "SMPL_WHILELOOP"
				|| StatList[i]->getType() == "VAR_IFCONDITION" || StatList[i]->getType() == "VAR_WHILELOOP")
			{
				DeleteConnector(StatList[i]->getTBranch());
				DeleteConnector(StatList[i]->getFBranch());
			}

			else
			{
				DeleteConnector(StatList[i]->getConnector());
			}

			Connect = StatList[i]->GetConnectorArray();
			count = StatList[i]->GetToCon();

			for (int k = 0; k < count; k++)
			{
				DeleteConnector(Connect[k]);
			}

			for (int j = i; j <= StatCount - 1; j++)
			{
				if (StatList[i]->getType() == "START")
				{
					int x = StatList[i]->GetStartCount();
					x--;
					StatList[i]->SetStartCount(x);

				}

				if (StatList[i]->getType() == "END")
				{
					int x = StatList[i]->GetEndCount();
					x--;
					StatList[i]->SetEndCount(x);
				}


				StatList[j] = StatList[j + 1];
			}

			StatCount--;
			unselect(DStat);
			delete S;
		}

	}

}
Statement *ApplicationManager::GetCopiedStatement() const
{
	return pCopiedStatement;

}
Statement*ApplicationManager::GetCutStatement() const
{
	return pCutStatement;
}
void ApplicationManager::Managerpaste(Statement*pstat)
{
	AddStatement(pstat);
}
void ApplicationManager::cutManager(Statement* s)
{
	for (int i = 0; i<StatCount; i++)
	{
		if (StatList[i] == s)
		{
			pCutStatement = StatList[i];
			for (int j = i; j<StatCount; j++)
			{
				StatList[j] = StatList[j + 1];
			}
			StatCount--;
		}
	}
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] == s->getConnector())
		{
			s->deleteCon(ConnList[i]);
			for (int j = i; j <= ConnCount - 1; j++)
			{
				ConnList[j] = ConnList[j + 1];
				ConnCount--;
			}
		}
	}
	for (int i = 0; i < ConnCount; i++)
	{
		Connector** c = s->GetConnectorArray();
		for (int k = 0; k<s->GetToCon(); k++)
		{
			if (ConnList[i] == c[k])
			{
				s->deleteCon(ConnList[i]);
				ConnList[i]->getSrcStat()->deleteCon(ConnList[i]);
				for (int j = i; j <= ConnCount - 1; j++)
				{
					ConnList[j] = ConnList[j + 1];
					ConnCount--;
				}
			}
		}
	}
}
/*void ApplicationManager::cutManager(Statement* s)
{
	for (int i = 0; i<StatCount; i++)
	{
		if (StatList[i] == s)
		{
			pCutStatement = StatList[i];
			for (int j = i; j<StatCount; j++)
			{
				StatList[j] = StatList[j + 1];
			}
			StatCount--;
		}
	}
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i] == s->getConnector())
		{
			for (int j = i; j <= ConnCount - 1; j++)
			{
				ConnList[j] = ConnList[j + 1];
				ConnCount--;
			}
		}
	}
}*/
bool ApplicationManager::Validate()
{
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->Valid(pOut) == false)
		{
			Lastmsg="chart is not valid"; return false;
		}
	}
	pOut->PrintMessage("Chart is Valid");
	Lastmsg = "Chart is Valid";
	for (int i = 0; i < StatCount; i++)
	{
		if (dynamic_cast<Condition*>(StatList[i]) != NULL)dynamic_cast<Condition*>(StatList[i])->initializeBlocks();
	}
	return true;
}

void ApplicationManager::DeleteConnector(Connector*Con)
{
	for (int i = 0; i < ConnCount; i++)
	{


		if (ConnList[i] == Con)
		{
			Connector*A = Con;
			for (int j = i; j <= ConnCount - 1; j++)


				ConnList[j] = ConnList[j + 1];

			ConnCount--;
			delete A;
		}
		
	}
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->getConnector() == Con)
			StatList[i]->deleteCon(Con);
	}
	unselectCon(Con);
}


void ApplicationManager::appAddConnector(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL

	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->InArea(P))
			return StatList[i];
	}
	///Add your code here to search for a statement given a point P(x,y)	

	return NULL;
}

Connector* ApplicationManager::GetConnector(Point P)const
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (ConnList[i]->InArea(P))
			return ConnList[i];
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

Connector* ApplicationManager::getSelectedConnector()const
{
	return SelectedCo;
}

Connector** ApplicationManager::getSelectedConnArray()
{
	return selectedConnectors;
}

int ApplicationManager::getCSelectCount()
{
	return CselectCount;
}
////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{	
	pSelectedStat = pStat;
	selectedarray[selectCount] = pStat;
	selectCount++;
}
void ApplicationManager::SetCopiedStatement(Statement*pStat)
{
	pCopiedStatement = pStat;

}

int ApplicationManager::GetSelectCount()
{
	return selectCount;
}

void ApplicationManager::SetSelectedConnector(Connector* c)
{
	SelectedCo = c;
	selectedConnectors[CselectCount] = c;
	CselectCount++;
}

Statement** ApplicationManager::getSelectArray()
{
	return selectedarray;
}
void ApplicationManager::unselect(Statement *pStat)
{
	if (selectCount == 1)
		pSelectedStat = NULL;
	else
		pSelectedStat = selectedarray[selectCount - 1];
	for (int i = 0; i<selectCount; i++)
	{
		if (selectedarray[i] == pStat)
		{
			for (int j = i; j<selectCount - 1; j++)
			{
				selectedarray[j] = selectedarray[j + 1];
			}
			selectCount--;
		}
	}
	pOut->ClearStatusBar();
}

void ApplicationManager::unselectCon(Connector* c)
{
	if (CselectCount == 1)
		SelectedCo = NULL;
	else
		SelectedCo = selectedConnectors[CselectCount - 1];
	for (int i = 0; i<CselectCount; i++)
	{
		if (selectedConnectors[i] == c)
		{
			for (int j = i; j<CselectCount - 1; j++)
			{
				selectedConnectors[j] = selectedConnectors[j + 1];
			}
			CselectCount--;
		}
	}
}
void ApplicationManager::SetCutStatement(Statement*pStat)
{
	pCopiedStatement = pStat;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	if (UI.AppMode == DESIGN)
		pOut->CreateDesignToolBar();
	else pOut->CreateSimulationToolBar();

	pOut->PrintMessage(Lastmsg);
	//Draw all statements
	for (int i = 0; i<StatCount; i++)
		StatList[i]->Draw(pOut);

	//Draw all connections
	for (int i = 0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////

//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<StatCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
	
}

int ApplicationManager::getStatCount() const
{
	return StatCount;
}

void ApplicationManager::setStatCount(int n)
{
	StatCount = n;
}

Statement* ApplicationManager::GetStatement(int id) const
{
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->getID() == id)
			return StatList[i];
	}	
	return NULL;
}

void ApplicationManager::Save() 
{
	string file;
	pOut->PrintMessage("Save as ..");
	file = pIn->GetString(pOut);
	pOut->PrintMessage("Saving file");
	file += ".txt";
	Outfile.open(file);
	Outfile << StatCount << "\n";
	for (int i = 0; i < StatCount; i++)
	{
		StatList[i]->Save(Outfile);
	}
	Outfile << ConnCount << "\n";
	for (int i = 0; i < ConnCount; i++)
	{
		ConnList[i]->Save(Outfile);
	}
	Outfile.close();
	pOut->PrintMessage("File saved");
	Lastmsg = "File saved";
}

StatementType ApplicationManager::getStatementType(string type)
{
	if (type == "START")
		return START;
	if (type == "END")
		return END;
	if (type == "READ")
		return READ;
	if (type == "WRITE")
		return WRITE;
	if (type == "SMPLASSIGN")
		return SMPLE_ASSIGNMENT;
	if (type == "VARASSIGN")
		return VAR_ASSIGNMENT;
	if (type == "SNGLOP")
		return SNGLOPERATOR;
	if (type == "SMPL_IFCONDITION")
		return SMPLE_IFCONDITIONAL;
	if (type == "VAR_IFCONDITION")
		return VAR_IFCONDITIONAL;
	if (type == "SMPL_WHILELOOP")
		return SMPLE_WHILELOOP;
	if (type == "VAR_WHILELOOP")
		return VAR_WHILELOOP;
	return NO_STAT;
}

void ApplicationManager::Load()
{
	string file;
	pOut->PrintMessage("Enter the file's name");
	file = pIn->GetString(pOut);
	pOut->PrintMessage("Loading file");
	file += ".txt";
	Infile.open(file);
	if (!Infile.is_open())
	{
		pOut->PrintMessage("File doesn't exist");
		Lastmsg = "File doesn't exist";
		return;
	}

	if (StatCount != 0)
	for (int i = 0; i < StatCount; i++)
	{
		delete StatList[i];
	}
	StatCount = 0;

	if (ConnCount !=0)
	for (int i = 0; i < StatCount; i++)
	{
		delete ConnList[i];
	}
	ConnCount = 0;

	int n;
	Infile >> n;

	Statement* pStat = NULL;

	for (int j = 0; j < n; j++)
	{
		string type;
		Infile >> type;
		StatementType stype = getStatementType(type);
		switch (stype)
		{
		case START:
			pStat = new Start;
			pStat->Load(Infile);
			AddStatement(pStat);
			break;
		case END:
			pStat = new End;
			pStat->Load(Infile);
			AddStatement(pStat);
			break;
		case READ:
			pStat = new Read;
			pStat->Load(Infile);
			AddStatement(pStat);
			break;
		case WRITE:
			pStat = new Write;
			pStat->Load(Infile);
			AddStatement(pStat);
			break;
		case SMPLE_ASSIGNMENT:
			pStat = new SmplAssign;
			pStat->Load(Infile);
			AddStatement(pStat);
			break;
		case VAR_ASSIGNMENT:
			pStat = new VarAssign;
			pStat->Load(Infile);
			AddStatement(pStat);
			break;
		case SNGLOPERATOR:
			pStat = new SnglOperator;
			pStat->Load(Infile);
			AddStatement(pStat);
			break;
		case SMPLE_IFCONDITIONAL:
			pStat = new SmpleIfCondition;
			pStat->Load(Infile);
			AddStatement(pStat);
			break;
		case VAR_IFCONDITIONAL:
			pStat = new VarIfCondition;
			pStat->Load(Infile);
			AddStatement(pStat);
			break;
		case SMPLE_WHILELOOP:
			pStat = new SmpleWhileLoop;
			pStat->Load(Infile);
			AddStatement(pStat);
			break;
		case VAR_WHILELOOP:
			pStat = new VarWhileLoop;
			pStat->Load(Infile);
			AddStatement(pStat);
			break;
		case NO_STAT:
			pOut->PrintMessage("Statement Invalid");
			Lastmsg = "Statement Invalid";
			return;
		}

	}

	Connector* pConn = NULL;
	Infile >> n;
	for (int j = 0; j < n; j++)
	{
		int id1, id2;
		Infile >> id1 >> id2;
		Statement* CurrSrc = GetStatement(id1);
		Statement* CurrDst = GetStatement(id2);
		
		if ((CurrSrc && CurrDst) != NULL)
		{
			pConn = new Connector(CurrSrc, CurrDst);
			pConn->Load(Infile);
			appAddConnector(pConn);
		}
		
	}
	Infile.close();
	Lastmsg = "File loaded";
}

void ApplicationManager::ZoomIn()
{
	if (!ZoomedIn)
	{
		for (int i = 0; i < StatCount; i++)
		{
			StatList[i]->ZoomIn(pOut);
		}
		for (int i = 0; i < ConnCount; i++)
		{
			ConnList[i]->ZoomIn();
		}
		if (ZoomedOut)
		{
			ZoomedIn = false;
			ZoomedOut = false;
		}
		else
		{
			ZoomedIn = true;
		}
	}
	Lastmsg = "";
}

void ApplicationManager::ZoomOut()
{
	if (!ZoomedOut)
	{
		for (int i = 0; i < StatCount; i++)
		{
			StatList[i]->ZoomOut(pOut);
		}
		for (int i = 0; i < ConnCount; i++)
		{
			ConnList[i]->ZoomOut();
		}
		if (ZoomedIn)
		{
			ZoomedOut = false;
			ZoomedIn = false;
		}
		else
		{
			ZoomedOut = true;
		}
	}
	Lastmsg = "";
}

Statement* ApplicationManager::GetStartStat()
{
	for (int i = 0; i < StatCount; i++) 

	{
		if (StatList[i]->getType() == "START")
		{
			return StatList[i];
		}

	}
}

vector<pair<string, double>>& ApplicationManager::getVariables()
{
	return Variables;
}

void ApplicationManager::setCodeVar()
{
	for (int i = 0; i < StatCount; i++)
	{
		bool exist = false;
		if (StatList[i]->getLHS() != "")
		{
			for (int j = i + 1; j<StatCount; j++)
			{
				if (StatList[i]->getLHS() == StatList[j]->getLHS())exist = true;
			}
			if (!exist) codeVariables.push_back(StatList[i]->getLHS());
		}
	}
}

vector<string>& ApplicationManager::getCodeVar()
{
	return codeVariables;
}