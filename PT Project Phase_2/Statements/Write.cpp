#include "Write.h"
#include "Condition.h"
#include <sstream>
using namespace std;

Write::Write(Point Lcorner, string N)
{
	Type = "WRITE";
	varName = N;
	Position = Lcorner;
	UpdateStatementText();

	pConn = NULL;	//No connectors yet
}

void Write::setname(const string &N)
{
	varName = N;
}

void Write::Draw(Output* pOut) const
{
	pOut->DrawReadWrite(Position, WRITE_WDTH, WRITE_HI, Text, Selected);
}

void Write::UpdateStatementText()
{
	if (varName == "")
		Text = "  ";
	else
	{
		ostringstream T;
		T << "Write " << varName;
		Text = T.str();
	}

	WRITE_WDTH = 18 * Text.size();
	WRITE_HI = 0.3*WRITE_WDTH;

	Inlet.x = Position.x + WRITE_HI / 2 + WRITE_WDTH / 2;
	Inlet.y = Position.y - WRITE_HI;

	Outlet.x = Position.x + WRITE_WDTH / 2;
	Outlet.y = Position.y;
}

Connector* Write::getConnector()
{
	return pConn;
}
void Write::setConnector(Connector* conn)
{
	pConn = conn;
}

void Write::setToConnector(Connector* C)
{
	toConnect[toCon] = C;
	toCon++;
}

Point Write::getInlet() const
{
	return Inlet;
}
Point Write::getOutlet() const
{
	return Outlet;
}

bool Write::InArea(Point p) const //to be implemented
{
	bool test = p.x > Position.x && p.x < (Position.x + WRITE_WDTH) && p.y >(Position.y - WRITE_HI) && p.y < (Position.y);
	return test;
}

void Write::Edit(Output*pOut, Input*pIn)
{

	pOut->PrintMessage("Enter variable");
	varName = pIn->GetString(pOut);

	UpdateStatementText();
}
void Write::setComment() //to be implemented
{}

Statement * Write::Copy() //to be implemented
{
	Statement*N = new Write(Position, varName);
	return N;
}

Statement* Write::Cut() //to be implemented
{
	Statement*N = new Write(Position, varName);
	return N;
}

Statement* Write::Paste() //to be implemented
{
	Statement*N = new Write(Position, varName);
	return N;
}


void Write::Move(Point &P) //to be implemented
{
	Position = P;
	Inlet.x = Position.x + WRITE_WDTH / 2 + WRITE_HI / 2;
	Inlet.y = Position.y - WRITE_HI;

	Outlet.x = Position.x + WRITE_WDTH / 2;
	Outlet.y = Position.y;
	if (pConn != NULL)
		pConn->setStartPoint(getOutlet());
	if (toCon != 0);
	for (int i = 0; i<toCon; i++)
	{
		toConnect[i]->setEndPoint(getInlet());
	}
}

void Write::Save(ofstream &OutFile)
{
	OutFile << Type << "\t" << ID << "\t" << Position.x << "\t" << Position.y << "\t" << varName << "\t" << Comment << "\n";
}

void Write::Load(ifstream &Infile)
{
	Infile >> ID;
	Infile >> Position.x >> Position.y;
	Infile >> varName;
	getline(Infile, Comment);
	UpdateStatementText();
}

void Write::ZoomIn(Output* & pOut) 
{
	font *= 1.2;
	pOut->setFont(font);
	WRITE_HI *= 1.2;
	WRITE_WDTH *= 1.2;
	Inlet.x = Position.x + WRITE_HI / 2 + WRITE_WDTH / 2;
	Inlet.y = Position.y - WRITE_HI;

	Outlet.x = Position.x + WRITE_WDTH / 2;
	Outlet.y = Position.y;
}

void Write::ZoomOut(Output* & pOut) 
{
	font /= 1.2;
	pOut->setFont(font);
	WRITE_HI /= 1.2;
	WRITE_WDTH /= 1.2;
	Inlet.x = Position.x + WRITE_HI / 2 + WRITE_WDTH / 2;
	Inlet.y = Position.y - WRITE_HI;

	Outlet.x = Position.x + WRITE_WDTH / 2;
	Outlet.y = Position.y;
}
bool Write::Valid(Output*pOut)
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
Statement* Write::GenerateCode(ofstream &OutFile)
{
	OutFile << "\tcout<< " << varName << "; \t"<<"//"<<Comment<<"\n";
	return pConn->getDstStat();
}

void Write::Simulate(vector<pair<string, double>>& variables, Input* pIn, Output* pOut)
{
	bool exist = false;
	double val;
	for (int i = 0; i < variables.size(); i++)
	{
		if (varName == variables.at(i).first)
		{
			val = variables.at(i).second;
			exist = true;
		}
	}
	if (!exist)
	{
		pOut->PrintMessage("No initial value");
		return;
	}
	ostringstream T;
	T << varName << " = " << val;
	string out = T.str();
	pOut->PrintMessage(out);
}

void Write::deleteCon(Connector*c)
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
Write::~Write() //to be implemented
{}