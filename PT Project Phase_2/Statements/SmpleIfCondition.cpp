
#include"VarIfCondition.h"
#include"SmpleIfCondition.h"
#include"SmpleWhileLoop.h"
#include"VarWhileLoop.h"

SmpleIfCondition::SmpleIfCondition(Point Ucorner, string LeftHS, double RightHS, string operation) : Condition(Ucorner,LeftHS,operation)
{
	Type = "SMPL_IFCONDITION";
	RHS = RightHS;
	UpdateStatementText();
	Endif = NULL;
}

void SmpleIfCondition::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void SmpleIfCondition::setOperat(const string& type)
{
	OPERATION = type;
	UpdateStatementText();
}

void SmpleIfCondition::setRHS(const double R)
{
	RHS = R;
	UpdateStatementText();
}

void SmpleIfCondition::UpdateStatementText()
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
}

void SmpleIfCondition::setBlock(Statement*)
{
	Statement* Ts = pConnTrue->getDstStat();
	Statement* Fs = pConnFalse->getDstStat();

	while (Ts->getConnector() != NULL)
	{
		for (int k = 0; k < TrueBlock.size(); k++)
		{
			if (Ts == TrueBlock.at(k))return;
		}

		Condition* temp_Tstat = dynamic_cast<Condition*>(Ts);

		if (dynamic_cast<SmpleIfCondition*>(Ts) != NULL || dynamic_cast<VarIfCondition*>(Ts) != NULL)
		{
			TrueBlock.push_back(Ts);
			temp_Tstat->setBlock(NULL);
			Ts = temp_Tstat->getEndBlock();
		}
		else if (dynamic_cast<SmpleWhileLoop*>(Ts) != NULL || dynamic_cast<VarWhileLoop*>(Ts) != NULL)
		{
			TrueBlock.push_back(Ts);
			temp_Tstat->setBlock(NULL);
			if (temp_Tstat->getEndBlock() == NULL){ valid = false; return; }
			Ts = temp_Tstat->getEndBlock();
		}
		else
		{
			TrueBlock.push_back(Ts);
			Ts = Ts->getConnector()->getDstStat();
		}
		if (Ts == this){ valid = false; return; }
	}

	while (Fs->getConnector() != NULL)
	{
		for (int k = 0; k < FalseBlock.size(); k++)
		{
			if (Fs == FalseBlock.at(k))return;
		}
		Condition* temp_Fstat = dynamic_cast<Condition*>(Fs);

		if (dynamic_cast<SmpleIfCondition*>(Fs) != NULL || dynamic_cast<VarIfCondition*>(Fs) != NULL)
		{
			FalseBlock.push_back(Fs);
			temp_Fstat->setBlock(NULL);
			Fs = temp_Fstat->getEndBlock();
		}
		else if (dynamic_cast<SmpleWhileLoop*>(Fs) != NULL || dynamic_cast<VarWhileLoop*>(Fs) != NULL)
		{
			FalseBlock.push_back(Fs);
			temp_Fstat->setBlock(NULL);
			if (temp_Fstat->getEndBlock() == NULL){ valid = false; return; }
			Fs = temp_Fstat->getEndBlock();
		}
		else
		{
			FalseBlock.push_back(Fs);
			Fs = Fs->getConnector()->getDstStat();
		}
		if (Fs == this){ valid = false; return; }
	}
	int i = 0;
	int j = 0;
	if (TrueBlock.size() > FalseBlock.size())
	{
		for (i; i < TrueBlock.size(); i++)
		{
			j = 0;
			for (j; j < FalseBlock.size(); j++)
			{
				if (TrueBlock.at(i) == FalseBlock.at(j))
				{
					Endif = TrueBlock.at(i);
					TrueBlock.resize(i);
					FalseBlock.resize(j);
				}
			}
		}
	}
	else
	{
		for (i; i < FalseBlock.size(); i++)
		{
			j = 0;
			for (j; j < TrueBlock.size(); j++)
			{
				if (FalseBlock.at(i) == TrueBlock.at(j))
				{
					Endif = FalseBlock.at(i);
					TrueBlock.resize(j);
					FalseBlock.resize(i);
				}
			}
		}
		
	}
	if (Endif == NULL)Endif = Ts;
}

void SmpleIfCondition::Edit(Output*pOut, Input*pIn)
{
	pOut->PrintMessage("Enter the variable name");
	LHS = pIn->GetString(pOut);

	pOut->PrintMessage("Enter operator");
	OPERATION = pIn->GetOperation(pOut);

	pOut->PrintMessage("Enter a value");
	RHS = pIn->GetValue(pOut);

	UpdateStatementText();


}

Statement* SmpleIfCondition::Copy()
{
	Statement*N = new SmpleIfCondition(Position, LHS, RHS);
	return N;
}

Statement* SmpleIfCondition::Cut()
{
	Statement*N = new SmpleIfCondition(Position, LHS, RHS);
	return N;
}

Statement* SmpleIfCondition::Paste()
{
	Statement*N = new SmpleIfCondition(Position, LHS, RHS);
	return N;
}


void SmpleIfCondition::Save(ofstream &OutFile)
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

void SmpleIfCondition::Load(ifstream &Infile)
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
	Infile>>RHS;
	getline(Infile, Comment);
	UpdateStatementText();
}

void SmpleIfCondition::Simulate(vector<pair<string, double>>& variables, Input*pIn, Output*pOut)
{
	relationalOperators rType;
	rType = getOperator(OPERATION);
	bool exist = false;
	int loc;
	for (int i = 0; i < variables.size(); i++)
	{
		if (LHS == variables.at(i).first)
		{
			exist = true;
			loc = i;
		}
	}
	if (exist)
	{
		switch (rType)
		{
		case IsEqual:
			if (variables.at(loc).second == RHS)
				Branch = true;
			else Branch = false;
			break;

		case NotEqual:
			if (variables.at(loc).second != RHS)
				Branch = true;
			else Branch = false;
			break;
		case Lessthan:
			if (variables.at(loc).second < RHS)
				Branch = true;
			else Branch = false;
			break;
		case LessthanOrEqual:
			if (variables.at(loc).second <= RHS)
				Branch = true;
			else Branch = false;
			break;
		case Greaterthan:
			if (variables.at(loc).second > RHS)
				Branch = true;
			else Branch = false;
			break;
		case GreaterthanOrEqual:
			if (variables.at(loc).second >= RHS)
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

void SmpleIfCondition::watch(vector<pair<string, double>>& variables, Output* pout)
{
	ostringstream T;
	for (int i = 0; i < variables.size(); i++)
	{
		if (LHS == variables.at(i).first)
		{
			T << LHS << variables.at(i).second;
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

SmpleIfCondition::~SmpleIfCondition() //To be implemented
{}

bool SmpleIfCondition::Valid(Output* pO)
{
	if (pConnTrue == NULL || pConnFalse == NULL)
	{
		pO->PrintMessage("Conditional statement must have two outlets");
		return false;
	}
	setBlock(NULL);
	if (valid == false)
	{
		pO->PrintMessage("If conditional statements must not have feedbacks");
		return false;
	}
	return true;
}

Statement* SmpleIfCondition::GenerateCode(ofstream& cppCode)
{
	if (TrueBlock.size() == 0 && FalseBlock.size() == 0)return Endif;
	if (TrueBlock.size() != 0 && FalseBlock.size() == 0) //no false block
	{
		cppCode << "\n\tif(" << Text << ")\t" << "//" << Comment << "\n\t{\n";
		for (int i = 0; i < TrueBlock.size(); i++)
		{
			cppCode << "\t\t";
			TrueBlock.at(i)->GenerateCode(cppCode);
		}
		cppCode << "\n\t}";
		return Endif;
	}
	else if (TrueBlock.size() == 0 && FalseBlock.size() != 0) //no true block
	{
		cppCode << "\n\tif(!(" << Text << "))\t" << "//" << Comment << "\n\t{\n";
		for (int i = 0; i < FalseBlock.size(); i++)
		{
			cppCode << "\t\t";
			FalseBlock.at(i)->GenerateCode(cppCode);
		}
		cppCode << "\n\t}";
		return Endif;
	}
	else //both true/false blocks exist
	{
		cppCode << "\n\tif(" << Text << ")\t" << "//" << Comment << "\n\t{\n";
		for (int i = 0; i < TrueBlock.size(); i++)
		{
			cppCode << "\t\t";
			TrueBlock.at(i)->GenerateCode(cppCode);
		}
		cppCode << "\n}\n\telse\n\t{\n";
		for (int i = 0; i < FalseBlock.size(); i++)
		{
			cppCode << "\t";
			FalseBlock.at(i)->GenerateCode(cppCode);
		}
		cppCode << "\n\t}";
		return Endif;
	}
}