#include "SmplAssign.h"
#include "Condition.h"

#include <sstream>

using namespace std;

SmplAssign::SmplAssign(Point Lcorner, string LeftHS, double RightHS)
{
	Type = "SMPLASSIGN";
	LHS = LeftHS;
	RHS = RightHS;
	Position = Lcorner;
	UpdateStatementText();

	pConn = NULL;	//No connectors yet
}

void SmplAssign::setLHS(string &L)
{
	LHS = L;
	UpdateStatementText();
}


void SmplAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void SmplAssign::Draw(Output* pOut) const
{
	pOut->DrawAssign(Position, ASSGN_WDTH, ASSGN_HI, Text, Selected);
}

//This function should be called when LHS or RHS changes
void SmplAssign::UpdateStatementText()
{
	if (LHS == "")	//No left handside ==>statement have no valid text yet
		Text = "    = ";
	else
	{
		//Build the statement text: Left handside then equals then right handside
		ostringstream T;
		T << LHS << " = " << RHS;
		Text = T.str();
	}

	ASSGN_WDTH = 20 * Text.size();
	ASSGN_HI = 0.3*ASSGN_WDTH;

	Inlet.x = Position.x + ASSGN_WDTH / 2;
	Inlet.y = Position.y;

	Outlet.x = Position.x + ASSGN_WDTH / 2;
	Outlet.y = Position.y + ASSGN_HI;
}

Connector* SmplAssign::getConnector()
{
	return pConn;
}

void SmplAssign::setConnector(Connector* conn)
{
	pConn = conn;
}

void SmplAssign::setToConnector(Connector* C)
{
	toConnect[toCon] = C;
	toCon++;
}

Point SmplAssign::getInlet() const
{
	return Inlet;
}
Point SmplAssign::getOutlet() const
{
	return Outlet;
}

bool SmplAssign::InArea(Point p) const //to be implemented
{
	bool test = Position.x <= p.x && p.x <= (Position.x + ASSGN_WDTH) && Position.y <= p.y && p.y <= (Position.y + ASSGN_HI);
	return test;
}

void SmplAssign::Edit(Output*pOut, Input*pIn)
{
	pOut->PrintMessage("Enter the variable name");
	LHS = pIn->GetString(pOut);


	pOut->PrintMessage("Enter a value");
	RHS = pIn->GetValue(pOut);

	UpdateStatementText();
		

}
void SmplAssign::setComment() 
{}

Statement* SmplAssign::Copy() 
{
	Statement*N = new SmplAssign(Position, LHS, RHS);
	return N;
}

Statement* SmplAssign::Cut() 
{
	Statement*N = new SmplAssign(Position, LHS, RHS);
	return N;
}

Statement* SmplAssign::Paste() 
{
	Statement*N = new SmplAssign(Position, LHS, RHS);
	return N;

}

void SmplAssign::Move(Point &P) //to be implemented
{
	Position = P;
	Inlet.x = Position.x + ASSGN_WDTH / 2;
	Inlet.y = Position.y;

	Outlet.x = Inlet.x;
	Outlet.y = Position.y + ASSGN_HI;
	if (pConn != NULL)
		pConn->setStartPoint(getOutlet());
	if (toCon != 0);
	for (int i = 0; i<toCon; i++)
	{
		toConnect[i]->setEndPoint(getInlet());
	}
}

void SmplAssign::Save(ofstream &OutFile) 
{
	OutFile << Type << "\t" << ID << "\t" << Position.x << "\t" << Position.y << "\t" << LHS << "\tEQUAL\t" << RHS
		<< "\t" << Comment << "\n";
}

void SmplAssign::Load(ifstream &Infile)
{
	Infile >> ID;
	Infile >> Position.x >> Position.y;
	Infile >> LHS;
	Infile.ignore(7);
	Infile >> RHS;
	getline(Infile, Comment);
	UpdateStatementText();
}

void SmplAssign::ZoomIn(Output* & pOut)
{
	font *= 1.2;
	pOut->setFont(font);
	ASSGN_HI *= 1.2;
	ASSGN_WDTH *= 1.2;
	Inlet.x = Position.x + ASSGN_WDTH / 2;
	Inlet.y = Position.y;

	Outlet.x = Position.x + ASSGN_WDTH / 2;
	Outlet.y = Position.y + ASSGN_HI;
}

void SmplAssign::ZoomOut(Output* & pOut)
{
	font /= 1.2;
	pOut->setFont(font);
	ASSGN_HI /= 1.2;
	ASSGN_WDTH /= 1.2;
	Inlet.x = Position.x + ASSGN_WDTH / 2;
	Inlet.y = Position.y;

	Outlet.x = Position.x + ASSGN_WDTH / 2;
	Outlet.y = Position.y + ASSGN_HI;
}

bool SmplAssign::Valid(Output*pOut)
{
	if (pConn == NULL)
		return false;

	Statement* current = this;
	while (current->getConnector() != NULL)
	{
		if (dynamic_cast<Condition*>(current) != NULL)
		{
			dynamic_cast<Condition*>(current)->setBlock(NULL);
			current = dynamic_cast<Condition*>(current)->getEndBlock();
		}
		else current = current->getConnector()->getDstStat();
		if (current == this)return false;
	}
	if (current->getConnector() == NULL && current->getType() == "END")return true;
	else return false;
}

Statement* SmplAssign::GenerateCode(ofstream &OutFile)
{
	OutFile << "\t" << Text << ";\t" << "//" << Comment << "\n";
	return pConn->getDstStat();
}

void SmplAssign::Simulate(vector<pair<string, double>>& variables, Input*pIn, Output*pOut)
{
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
		variables.at(loc).second = RHS;
	}
	else
	{
		varNameVal.first = LHS;
		varNameVal.second = RHS;
		variables.push_back(varNameVal);
	}
}



void SmplAssign::watch(vector<pair<string, double>>& variables, Output* pout)
{
	ostringstream T;
	T << LHS << " = " << RHS;
	string out = T.str();
	pout->PrintMessage(out);
	out = "";
}

void SmplAssign::deleteCon(Connector*c)
{
	if (c = pConn)
		pConn = NULL;
	else
	{
		for (int i = 0; i < toCon; i++)
		{
			if (c == toConnect[i])
			{
				for (int j = i; j < toCon; j++)
					toConnect[j] = toConnect[j + 1];
				toCon--;
			}
		}
	}
}
SmplAssign::~SmplAssign() //to be implemented
{}