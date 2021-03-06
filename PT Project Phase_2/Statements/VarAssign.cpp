#include "VarAssign.h"
#include "Condition.h"
#include <sstream>

using namespace std;

VarAssign::VarAssign(Point Lcorner, string LeftHS, string RightHS)
{
	Type = "VARASSIGN";
	LHS = LeftHS;
	RHS = RightHS;
	Position = Lcorner;
	UpdateStatementText();
	pConn = NULL;	//No connectors yet
	RHSexist = false;
}

void VarAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void VarAssign::setRHS(const string&L)
{
	RHS = L;
	UpdateStatementText();
}

void VarAssign::Draw(Output* pOut) const
{
	pOut->DrawAssign(Position, ASSGN_WDTH, ASSGN_HI, Text, Selected);
}

//This function should be called when LHS or RHS changes
void VarAssign::UpdateStatementText()
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

Connector* VarAssign::getConnector()
{
	return pConn;
}

void VarAssign::setConnector(Connector* conn)
{
	pConn = conn;
}

void VarAssign::setToConnector(Connector* C)
{
	toConnect[toCon] = C;
	toCon++;
}

Point VarAssign::getInlet() const
{
	return Inlet;
}
Point VarAssign::getOutlet() const
{
	return Outlet;
}

bool VarAssign::InArea(Point p) const //to be implemented
{
	bool test = Position.x <= p.x && p.x <= (Position.x + ASSGN_WDTH) && Position.y <= p.y && p.y <= (Position.y + ASSGN_HI);
	return test;
}

void VarAssign::Edit(Output*pOut, Input*pIn)
{
	pOut->PrintMessage("Enter the variable name");
	LHS = pIn->GetString(pOut);


	pOut->PrintMessage("Enter a value");
	RHS = pIn->GetString(pOut);

	UpdateStatementText();

}
void VarAssign::setComment() //to be implemented
{}

Statement* VarAssign::Copy() //to be implemented
{
	Statement*N = new VarAssign(Position, LHS, RHS);
	return N;
}

Statement* VarAssign::Cut() //to be implemented
{
	Statement*N = new VarAssign(Position, LHS, RHS);
	return N;
}

Statement* VarAssign::Paste() //to be implemented
{
	Statement*N = new VarAssign(Position, LHS, RHS);
	return N;
}


void VarAssign::Move(Point &P) //to be implemented
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

void VarAssign::Save(ofstream &OutFile)
{
	OutFile << Type << "\t" << ID << "\t" << Position.x << "\t" << Position.y << "\t" << LHS << "\tEQUAL\t" << RHS
		<< "\t" << Comment << "\n";
}

void VarAssign::Load(ifstream &Infile)
{
	Infile >> ID;
	Infile >> Position.x >> Position.y;
	Infile >> LHS;
	Infile.ignore(7);
	Infile >> RHS;
	getline(Infile, Comment);
	UpdateStatementText();
}

void VarAssign::ZoomIn(Output* & pOut) //to be implemented
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

void VarAssign::ZoomOut(Output* & pOut) //to be implemented
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

bool VarAssign::Valid(Output*pOut)
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

Statement* VarAssign::GenerateCode(ofstream &OutFile)
{
	OutFile << "\t" << Text << ";\t" << "//" << Comment << "\n";
	return pConn->getDstStat();
}

void VarAssign::Simulate(vector<pair<string, double>>& variables, Input*pIn, Output*pOut)
{
	bool LHSexist = false;
	RHSexist = false;
	int LHSloc, RHSloc;

	for (int i = 0; i < variables.size(); i++)
	{
		if (RHS == variables.at(i).first)
		{
			RHSexist = true;
			RHSloc = i;
		}
	}

	for (int i = 0; i < variables.size(); i++)
	{
		if (LHS == variables.at(i).first)
		{
			LHSexist = true;
			LHSloc = i;
		}
	}

	if (!RHSexist)
	{
		pOut->PrintMessage("undefined right handside"); return;
	}

	if (LHSexist)
	{
		variables.at(LHSloc).second = variables.at(RHSloc).second;
	}
	else
	{
		varNameVal.first = LHS;
		varNameVal.second = variables.at(RHSloc).second;
		variables.push_back(varNameVal);
	}
}

void VarAssign::watch(vector<pair<string, double>>& variables, Output* pout)
{
	ostringstream T;
	if (RHSexist)
	for (int i = 0; i < variables.size(); i++)
	{
		if (RHS == variables.at(i).first)
		{
			T << LHS << " = " << RHS << " = " << variables.at(i).second;
		}
	}
	else
		T << RHS << " undefined";
	string out = T.str();
	pout->PrintMessage(out);
	out = "";
}

void VarAssign::deleteCon(Connector*c)
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

VarAssign::~VarAssign() //to be implemented
{}