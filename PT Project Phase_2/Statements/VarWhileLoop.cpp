
#include"VarIfCondition.h"
#include"SmpleIfCondition.h"
#include"SmpleWhileLoop.h"
#include"VarWhileLoop.h"

VarWhileLoop::VarWhileLoop(Point Ucorner, string LeftHS, string RightHS, string operation) : Condition(Ucorner, LeftHS, operation)
{
	Type = "VAR_WHILELOOP";
	RHS = RightHS;
	UpdateStatementText();
	EndLoop = NULL;
	LHSexist = false;
	RHSexist = false;
}

void VarWhileLoop::setRHS(const string &R)
{
	RHS = R;
	UpdateStatementText();
}

void VarWhileLoop::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void VarWhileLoop::setOperat(const string& type)
{
	OPERATION = type;
	UpdateStatementText();
}


void VarWhileLoop::UpdateStatementText()
{
	if (LHS == "")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then the operation then right handside
		ostringstream T;
		T << LHS << "  " << OPERATION << "  " << RHS;
		Text = T.str();
	}
	COND_DIAG2 = 18 * Text.size();
	COND_DIAG1 = 0.4*COND_DIAG2;

	Inlet.x = Position.x;
	Inlet.y = Position.y;

	OutletTrue.x = Position.x - (COND_DIAG2 / 2);
	OutletFalse.x = Position.x + (COND_DIAG2 / 2);

	OutletTrue.y = Position.y + (COND_DIAG1 / 2);
	OutletFalse.y = Position.y + (COND_DIAG1 / 2);
	EndLoop = NULL;
}

void VarWhileLoop::setBlock(Statement* Parent)
{
	Statement* Ts = pConnTrue->getDstStat();
	Statement* Fs = pConnFalse->getDstStat();

	while (Ts->getConnector() != NULL)
	{
		for (int k = 0; k < loop.size(); k++)
		{
			if (Ts == loop.at(k)) return;
		}
		if (Ts == this) { EndLoop = pConnFalse->getDstStat(); direction = true; return; }

		Condition* TempTs = dynamic_cast<Condition*>(Ts);

		if (dynamic_cast<SmpleIfCondition*>(Ts) != NULL || dynamic_cast<VarIfCondition*>(Ts) != NULL)
		{
			loop.push_back(Ts);
			TempTs->setBlock(NULL);
			if (TempTs->getEndBlock() == NULL){ return; }
			Ts = TempTs->getEndBlock();
		}
		else if ((dynamic_cast<SmpleWhileLoop*>(Ts) != NULL || dynamic_cast<VarWhileLoop*>(Ts) != NULL)
			&& Ts != Parent)
		{
			loop.push_back(Ts);
			TempTs->setBlock(this);
			Ts = TempTs->getEndBlock();
		}
		else if (Ts != Parent)
		{
			loop.push_back(Ts);
			Ts = Ts->getConnector()->getDstStat();
		}
		if (Ts == Parent)break;
	}
	loop.clear();
	while (Fs->getConnector() != NULL)
	{
		for (int k = 0; k < loop.size(); k++)
		{
			if (Fs == loop.at(k)) return;
		}
		if (Fs == this) { EndLoop = pConnTrue->getDstStat(); direction = false; return; }

		Condition* TempFs = dynamic_cast<Condition*>(Fs);

		if (dynamic_cast<SmpleIfCondition*>(Fs) != NULL || dynamic_cast<VarIfCondition*>(Fs) != NULL)
		{
			loop.push_back(Fs);
			TempFs->setBlock(NULL);
			if (TempFs->getEndBlock() == NULL){ return; }
			Fs = TempFs->getEndBlock();
		}
		else if ((dynamic_cast<SmpleWhileLoop*>(Fs) != NULL || dynamic_cast<VarWhileLoop*>(Fs) != NULL)
			&& Fs != Parent)
		{
			loop.push_back(Fs);
			TempFs->setBlock(this);
			Fs = TempFs->getEndBlock();
		}
		else if (Fs != Parent)
		{
			loop.push_back(Fs);
			Fs = Fs->getConnector()->getDstStat();
		}
		if (Fs == Parent)break;
	}
}


/* To be implemented */

void VarWhileLoop::Edit(Output*pOut, Input*pIn)
{
	pOut->PrintMessage("Enter the variable name");
	LHS = pIn->GetString(pOut);

	pOut->PrintMessage("Enter operator");
	OPERATION = pIn->GetOperation(pOut);

	pOut->PrintMessage("Enter a value");
	RHS = pIn->GetString(pOut);

	UpdateStatementText();

}

Statement* VarWhileLoop::Copy()
{
	Statement*N = new VarWhileLoop(Position, LHS, RHS);
	return N;
}

Statement* VarWhileLoop::Cut()
{
	Statement*N = new VarWhileLoop(Position, LHS, RHS);
	return N;
}

Statement* VarWhileLoop::Paste()
{
	Statement*N = new VarWhileLoop(Position, LHS, RHS);
	return N;
}

void VarWhileLoop::Save(ofstream &OutFile)
{
	relationalOperators rType;
	OutFile << Type << "\t" << ID << "\t" << Position.x << "\t" << Position.y << "\t" << LHS << "\t";
	rType = getOperator(OPERATION);

	switch (rType)
	{
	case IsEqual:
		OutFile << "Is_EQUAL";
		break;

	case NotEqual:
		OutFile << "Nt_EQUAL";
		break;

	case Lessthan:
		OutFile << "LESS";
		break;

	case LessthanOrEqual:
		OutFile << "LESS_EQ";
		break;

	case Greaterthan:
		OutFile << "GRT";
		break;

	case GreaterthanOrEqual:
		OutFile << "GRT_EQ";
		break;

	case NoOperation:
		OutFile << "Invalid_operation";
		break;
	}
	OutFile << "\t" << RHS << "\t" << Comment << "\n";
}

void VarWhileLoop::Load(ifstream &Infile)
{
	string opName;
	Infile >> ID;
	Infile >> Position.x >> Position.y;
	Infile >> LHS >> opName;
	if (opName == "Is_EQUAL")
		OPERATION = "==";
	else if (opName == "Nt_EQUAL")
		OPERATION = "!=";
	else if (opName == "LESS")
		OPERATION = "<";
	else if (opName == "LESS_EQ")
		OPERATION = "<=";
	else if (opName == "GRT")
		OPERATION = ">";
	else if (opName == "GRT_EQ")
		OPERATION = ">=";
	else OPERATION = "";
	Infile >> RHS;
	getline(Infile, Comment);
	UpdateStatementText();
}

void VarWhileLoop::Simulate(vector<pair<string, double>>& variables, Input*pIn, Output*pOut)
{
	relationalOperators rType;
	rType = getOperator(OPERATION);
	LHSexist = false;
	RHSexist = false;
	int LHSloc, RHSloc;
	for (int i = 0; i < variables.size(); i++)
	{
		if (LHS == variables.at(i).first)
		{
			LHSexist = true;
			LHSloc = i;
		}
	}

	for (int i = 0; i < variables.size(); i++)
	{
		if (RHS == variables.at(i).first)
		{
			RHSexist = true;
			RHSloc = i;
		}
	}

	if (LHSexist && RHSexist)
	{
		switch (rType)
		{
		case IsEqual:
			if (variables.at(LHSloc).second == variables.at(RHSloc).second)
				Branch = true;
			else Branch = false;
			break;

		case NotEqual:
			if (variables.at(LHSloc).second != variables.at(RHSloc).second)
				Branch = true;
			else Branch = false;
			break;
		case Lessthan:
			if (variables.at(LHSloc).second < variables.at(RHSloc).second)
				Branch = true;
			else Branch = false;
			break;
		case LessthanOrEqual:
			if (variables.at(LHSloc).second <= variables.at(RHSloc).second)
				Branch = true;
			else Branch = false;
			break;
		case Greaterthan:
			if (variables.at(LHSloc).second > variables.at(RHSloc).second)
				Branch = true;
			else Branch = false;
			break;
		case GreaterthanOrEqual:
			if (variables.at(LHSloc).second >= variables.at(RHSloc).second)
				Branch = true;
			else Branch = false;
			break;
		case NoOperation:
			pOut->PrintMessage("Invalid operation");
			break;
		}
	}
	else
	{
		pOut->PrintMessage("Variable doesn't exist");
	}
}

Statement* VarWhileLoop::GenerateCode(ofstream& cppCode)
{
	if (direction)
		cppCode << "\n\twhile( " << Text << ")\t" << "//" << Comment << "\n\t{\n";
	else cppCode << "\n\twhile(!( " << Text << "))\t" << "//" << Comment << "\n\t{\n";
	for (int i = 0; i < loop.size(); i++)
	{
		cppCode << "\t\t";
		loop.at(i)->GenerateCode(cppCode);
	}
	cppCode << "\n\t}";
	return EndLoop;
}

void VarWhileLoop::watch(vector<pair<string, double>>& variables, Output* pout)
{
	ostringstream T;
	if (LHSexist)
	{
		for (int i = 0; i < variables.size(); i++)
		if (LHS == variables.at(i).first)
			T << LHS << " = " << variables.at(i).second;
		if (RHSexist)
		{
			for (int i = 0; i < variables.size(); i++)
			if (RHS == variables.at(i).first)
				T << RHS << " = " << variables.at(i).second;
		}
		else
		{
			T << RHS << "does not exist";
		}
	}
	else
	{
		T << LHS << "does not exist";
		if (RHSexist)
		{
			for (int i = 0; i < variables.size(); i++)
			if (RHS == variables.at(i).first)
				T << RHS << " = " << variables.at(i).second;
		}
		else
		{
			T << RHS << "does not exist";
		}
	}
	if (Branch)
		T << "true";
	else
		T << "false";
	string out = T.str();
	pout->PrintMessage(out);
	out = "";
}

bool VarWhileLoop::Valid(Output* pO)
{
	if (pConnTrue == NULL || pConnFalse == NULL)
	{
		pO->PrintMessage("While loops must have two outlets");
		return false;
	}
	setBlock(NULL);
	if (EndLoop == NULL)
	{
		pO->PrintMessage("No loops detected");
		return false;
	}
	return true;
}

VarWhileLoop::~VarWhileLoop() //to be implemented
{}