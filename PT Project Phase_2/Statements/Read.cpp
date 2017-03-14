#include "Read.h"
#include "Condition.h"
#include <sstream>
using namespace std;

Read::Read(Point Lcorner, string N)
{
	Type = "READ";
	varName = N;
	Position = Lcorner;
	UpdateStatementText();
	pConn = NULL;	//No connectors yet
}

void Read::setname(const string &N)
{
	varName = N;
}

void Read::Draw(Output* pOut) const
{
	pOut->DrawReadWrite(Position, READ_WDTH, READ_HI, Text, Selected);
}

void Read::UpdateStatementText()
{
	if (varName == "")
		Text = "  ";
	else
	{
		ostringstream T;
		T << "Read " << varName;
		Text = T.str();
	}

	READ_WDTH = 18 * Text.size();
	READ_HI = 0.3*READ_WDTH;

	Inlet.x = Position.x + READ_HI / 2 + READ_WDTH / 2;
	Inlet.y = Position.y - READ_HI;

	Outlet.x = Position.x + READ_WDTH / 2;
	Outlet.y = Position.y;
}

Connector* Read::getConnector()
{
	return pConn;
}
void Read::setConnector(Connector* conn)
{
	pConn = conn;
}

void Read::setToConnector(Connector* C)
{
	toConnect[toCon] = C;
	toCon++;
}

Point Read::getInlet() const
{
	return Inlet;
}
Point Read::getOutlet() const
{
	return Outlet;
}

bool Read::InArea(Point p) const //to be implemented
{
	if (p.x >= Position.x && p.x <= Position.x + READ_WDTH + READ_HI / 2 && p.y >= Position.y - READ_HI && p.y <= Position.y)
	{
		for (int i = 0; i <= READ_HI; i++)
		{
			if (p.y == Position.y - i)
				return (p.x >= Position.x + 0.5*i && p.x <= Position.x + READ_WDTH + 0.5*i);
		}
	}
	return false;
}

void Read::Edit(Output*pOut, Input*pIn)
{

	pOut->PrintMessage("Enter variable");
	varName = pIn->GetString(pOut);
	UpdateStatementText();

}

void Read::setComment() //to be implemented
{}

Statement* Read::Copy() //to be implemented
{
	Statement*N = new Read(Position, varName);
	return N;
}

Statement* Read::Cut() //to be implemented
{
	Statement*N = new Read(Position, varName);
	return N;
}
Statement * Read::Paste() //to be implemented
{
	Statement* M = new Read(Position, varName);
	return M;
}


void Read::Move(Point &P) //to be implemented
{
	Position = P;
	Inlet.x = Position.x + READ_WDTH / 2 + READ_HI/2;
	Inlet.y = Position.y - READ_HI;

	Outlet.x = Position.x + READ_WDTH/2;
	Outlet.y = Position.y;
	if (pConn != NULL)
		pConn->setStartPoint(getOutlet());
	if (toCon != 0);
	for (int i = 0; i<toCon; i++)
	{
		toConnect[i]->setEndPoint(getInlet());
	}
}

void Read::Save(ofstream &OutFile)
{
	OutFile << Type << "\t" << ID << "\t" << Position.x << "\t" << Position.y << "\t" << varName << "\t" << Comment << "\n";
}

void Read::Load(ifstream &Infile)
{
	Infile >> ID;
	Infile >> Position.x >> Position.y;
	Infile >> varName;
	getline(Infile, Comment);
	UpdateStatementText();
}

void Read::ZoomIn(Output* & pOut) 
{
	font *= 1.2;
	pOut->setFont(font);
	READ_HI *= 1.2;
	READ_WDTH *= 1.2;
	Inlet.x = Position.x + READ_HI / 2 + READ_WDTH / 2;
	Inlet.y = Position.y - READ_HI;

	Outlet.x = Position.x + READ_WDTH / 2;
	Outlet.y = Position.y;
}

void Read::ZoomOut(Output* & pOut)
{
	font /= 1.2;
	pOut->setFont(font);
	READ_HI /= 1.2;
	READ_WDTH /= 1.2;
	Inlet.x = Position.x + READ_HI / 2 + READ_WDTH / 2;
	Inlet.y = Position.y - READ_HI;

	Outlet.x = Position.x + READ_WDTH / 2;
	Outlet.y = Position.y;
}

bool Read::Valid(Output*pOut)
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

Statement* Read::GenerateCode(ofstream &OutFile)
{
	OutFile << "\tcin>>" << varName << ";\t"<<"//"<<Comment<<"\n";
	return pConn->getDstStat();
}

void Read::Simulate(vector<pair<string, double>>& variables, Input* pIn, Output* pOut)
{
	varNameVal.first = varName;
	string temp = "Enter the value of " + varName;
	pOut->PrintMessage(temp);
	varNameVal.second = pIn->GetValue(pOut);
	variables.push_back(varNameVal);
}

void Read::deleteCon(Connector*c)
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
Read::~Read() //to be implemented
{}