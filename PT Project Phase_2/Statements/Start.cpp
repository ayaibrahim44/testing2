#include "Start.h"
#include "Condition.h"
#include <sstream>
using namespace std;

int Start::start_count = 0;

Start::Start(Point Lcorner)
{

	pConn = NULL;	//No connectors yet
	Text = "Start";
	Type = "START";
	Position = Lcorner;
	UpdateStatementText();

	start_count++;
}

void Start::UpdateStatementText()
{
	Outlet.x = Position.x + UI.START_END_WDTH / 2;
	Outlet.y = Position.y + UI.START_END_HI;
}


void Start::Draw(Output* pOut) const
{
	pOut->DrawStartEnd(Position, UI.START_END_WDTH, UI.START_END_HI, Text, Selected);
}

Point Start::getOutlet() const
{
	return Outlet;
}

void Start::setConnector(Connector* conn)
{
	pConn = conn;
}

Connector* Start::getConnector()
{
	return pConn;
}

bool Start::InArea(Point p) const //to be implemented
{
	int h = Position.x + (UI.START_END_WDTH / 2);
	int k = Position.y + (UI.START_END_HI / 2);
	float a = pow(p.x - h, 2) / pow(UI.START_END_WDTH / 2, 2);
	float b = pow(p.y - k, 2) / pow(UI.START_END_HI / 2, 2);
	return (a + b <= 1);
}

void Start::Edit(Output*, Input*) //to be implemented
{
}

void Start::setComment() //to be implemented
{}


Statement* Start::Copy() //to be implemented
{
	Statement*N = new Start(Position);
	return N;
}

Statement* Start::Cut() //to be implemented
{
	Statement*N = new Start(Position);
	return N;
}

Statement* Start::Paste() //to be implemented
{
	Statement*N = new Start(Position);
	return N;

}

void Start::Move(Point &P) //to be implemented
{
	Position = P;
	Outlet.x = Position.x + UI.START_END_WDTH / 2;
	Outlet.y = Position.y;
	if (pConn != NULL)
		pConn->setStartPoint(getOutlet());
}

void Start::Save(ofstream &OutFile)
{
	OutFile << Type << "\t" << ID << "\t" << Position.x << "\t" << Position.y << "\t" << Comment << "\n";
}

void Start::Load(ifstream &Infile)
{
	Infile >> ID;
	Infile >> Position.x >> Position.y;
	getline(Infile,Comment);
	UpdateStatementText();
}

void Start::ZoomIn(Output* & pOut) 
{
	font *= 1.2;
	pOut->setFont(font);
	UI.START_END_HI *= 1.2;
	UI.START_END_WDTH *= 1.2;
	Outlet.x = Position.x + UI.START_END_WDTH / 2;
	Outlet.y = Position.y + UI.START_END_HI;
}

void Start::ZoomOut(Output* & pOut)
{
	font /= 1.2;
	pOut->setFont(font);
	UI.START_END_HI /= 1.2;
	UI.START_END_WDTH /= 1.2;
	Outlet.x = Position.x + UI.START_END_WDTH / 2;
	Outlet.y = Position.y + UI.START_END_HI;
}

bool Start::Valid(Output*pOut)
{
	if (start_count != 1)
		pOut->PrintMessage("there is more one start");
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

Statement* Start::GenerateCode(ofstream &OutFile)
{
	OutFile << "\n#include<iostream>\nusing namespace std;\nvoid main()\n{\n\t"<<"//"<<Comment<<"\n";
	return pConn->getDstStat();
}

void Start::Simulate(vector<pair<string, double>>&, Input*, Output*) //no implementation
{}

void Start::watch(vector<pair<string, double>>& variables, Output* pout)
{
	ostringstream T;
	T << "Start";
	string out = T.str();
	pout->PrintMessage(out);
	out = "";
}

void Start::deleteCon(Connector*c)
{
	if (c = pConn)
		pConn = NULL;
}
Start::~Start() //to be implemented
{}