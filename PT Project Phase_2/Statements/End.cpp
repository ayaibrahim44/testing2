#include "End.h"
#include <sstream>
using namespace std;

int End::end_count = 0;

End::End(Point Lcorner)
{
	Text = "End";
	Type = "END";
	Position = Lcorner;
	UpdateStatementText();

	end_count++;
 
}

void End::UpdateStatementText()
{
	Inlet.x = Position.x + UI.START_END_WDTH / 2;
	Inlet.y = Position.y;
}

void End::setToConnector(Connector* C)
{
	toConnect[toCon] = C;
	toCon++;
}

void End::Draw(Output* pOut) const
{
	pOut->DrawStartEnd(Position, UI.START_END_WDTH, UI.START_END_HI, Text, Selected);
}

Point End::getInlet() const
{
	return Inlet;
}

bool End::InArea(Point p) const //to be implemented
{
	int h = Position.x + (UI.START_END_WDTH / 2);
	int k = Position.y + (UI.START_END_HI / 2);
	float a = pow(p.x - h, 2) / pow(UI.START_END_WDTH / 2, 2);
	float b = pow(p.y - k, 2) / pow(UI.START_END_HI / 2, 2);
	return (a + b <= 1);
}

void End::Edit(Output*, Input*) //to be implemented
{}

void End::setComment() //to be implemented
{}


Statement* End::Copy() //to be implemented
{
	Statement*N = new End(Position);
	return N;
}

Statement* End::Cut() //to be implemented
{
	Statement*N = new End(Position);
	return N;
}

Statement* End::Paste() //to be implemented
{
	Statement*N = new End(Position);
	return N;
}
void End::Move(Point& P) //to be implemented
{
	Position = P;
	Inlet.x = Position.x + UI.START_END_WDTH / 2;
	Inlet.y = Position.y;
	if (toCon != 0)
	for (int i = 0; i < toCon; i++)
		toConnect[i]->setEndPoint(getInlet());
}


void End::Save(ofstream &OutFile)
{
	OutFile << Type << "\t" << ID << "\t" << Position.x << "\t" << Position.y << "\t" << Comment << "\n";
}

void End::Load(ifstream &Infile)
{
	Infile >> ID;
	Infile >> Position.x >> Position.y;
	getline(Infile, Comment);
	UpdateStatementText();
}

void End::ZoomIn(Output* & pOut) 
{
	font *= 1.2;
	pOut->setFont(font);
	UI.START_END_HI *= 1.2;
	UI.START_END_WDTH *= 1.2;
	Inlet.x = Position.x + UI.START_END_WDTH / 2;
	Inlet.y = Position.y;
}

void End::ZoomOut(Output* & pOut)
{
	font /= 1.2;
	pOut->setFont(font);
	UI.START_END_HI /= 1.2;
	UI.START_END_WDTH /= 1.2;
	Inlet.x = Position.x + UI.START_END_WDTH / 2;
	Inlet.y = Position.y;
}

bool End::Valid(Output*pOut)
{
	if (end_count == 1)
		return true;
	else
	{
		pOut->PrintMessage("there is more one end");
		return false;
	}

}

Statement* End::GenerateCode(ofstream &OutFile)
{
	OutFile << "\n}\t" << "//" << Comment << "\n";
	return NULL;
}

void End::Simulate(vector<pair<string, double>>&, Input*, Output*) //no implementation
{}

void End::watch(vector<pair<string, double>>& variables, Output* pout)
{
	ostringstream T;
	T << "End";
	string out = T.str();
	pout->PrintMessage(out);
	out = "";
}
void End::deleteCon(Connector*c)
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
End::~End() //to be implemented
{}