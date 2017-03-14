#include "SnglOperator.h"
#include "Condition.h"
#include <sstream>
#include<string>
#include<algorithm>

using namespace std;

SnglOperator::SnglOperator(Point Lcorner, string LeftHS, string RightHS)
{
	Type = "SNGLOP";
	LHS = LeftHS;
	RHS = RightHS;
	Position = Lcorner;
	UpdateStatementText();
	pConn = NULL;	//No connectors yet
	RHSexist1 = false;
	RHSexist2 = false;
	RHSexist = false;
}

void SnglOperator::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void SnglOperator::setRHS(const string &R)
{
	RHS = R;
	UpdateStatementText();
}

void SnglOperator::SplitRhs()
{
	string rhs,lhs;
	for (int i = 0; i < RHS.size(); i++)
	{
		if (RHS[i] == ' ');
		else rhs += RHS[i];
	}
	RHS = rhs;
	for (int i = 0; i < LHS.size(); i++)
	{
		if (LHS[i] == ' ');
		else lhs += LHS[i];
	}
	LHS = lhs;

	if (Rhs.size() != 0)
		Rhs.clear();
	stringstream T1;
	T1 << RHS;
	string oprand1;

	while (getline(T1, oprand1, '+'))
	{
		Rhs.push_back(oprand1);
	}
	if (Rhs.size() == 2)
	{
		oper = '+';
		return;
	}
	
	stringstream T2;
	T2 << RHS;
	string oprand2;
	if (Rhs.size() != 0)
		Rhs.clear();

	while (getline(T2, oprand2, '-'))
	{
		Rhs.push_back(oprand2);
	}
	if (Rhs.size() == 2)
	{
		oper = '-';
		return;
	}

	stringstream T3;
	T3 << RHS;
	string oprand3;
	if (Rhs.size() != 0)
		Rhs.clear();

	while (getline(T3, oprand3, '*'))
	{
		Rhs.push_back(oprand3);
	}
	if (Rhs.size() == 2)
	{
		oper = '*';
		return;
	}

	stringstream T4;
	T4 << RHS;
	string oprand4;
	if (Rhs.size() != 0)
		Rhs.clear();

	while (getline(T4, oprand4, '/'))
	{
		Rhs.push_back(oprand4);
	}
	if (Rhs.size() == 2)
	{
		oper = '/';
		return;
	}

}

pair<bool, bool> SnglOperator::checkType() //if strings stored are double return false
{
	pair<bool, bool> temp_check;
	SplitRhs();
	
	if (Rhs.at(0)[0] >= 45 && Rhs.at(0)[0] < 58 && Rhs.at(0)[0] != 47)
		temp_check.first = false;
	else temp_check.first = true;

	if (Rhs.at(1)[0] >= 45 && Rhs.at(1)[0] < 58 && Rhs.at(1)[0] != 47)
		temp_check.second = false;
	else temp_check.second = true;

	return temp_check;
}

void SnglOperator::Draw(Output* pOut) const
{
	pOut->DrawAssign(Position, ASSGN_WDTH, ASSGN_HI, Text, Selected);
}
//This function should be called when LHS or RHS changes
void SnglOperator::UpdateStatementText()
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

Connector* SnglOperator::getConnector()
{
	return pConn;
}

void SnglOperator::setConnector(Connector* conn)
{
	pConn = conn;
}

void SnglOperator::setToConnector(Connector* C)
{
	toConnect[toCon] = C;
	toCon++;
}

Point SnglOperator::getInlet() const
{
	return Inlet;
}
Point SnglOperator::getOutlet() const
{
	return Outlet;
}

bool SnglOperator::InArea(Point p) const //to be implemented
{
	bool test = Position.x <= p.x && p.x <= (Position.x + ASSGN_WDTH) && Position.y <= p.y && p.y <= (Position.y + ASSGN_HI);
	return test;
}

void SnglOperator::Edit(Output*pOut, Input*pIn)
{
	pOut->PrintMessage("Enter the variable name");
	LHS = pIn->GetString(pOut);


	pOut->PrintMessage("Enter a value");
	RHS = pIn->GetString(pOut);

	UpdateStatementText();


}
void SnglOperator::setComment() //to be implemented
{}


Statement* SnglOperator::Copy() //to be implemented
{
	Statement*N = new SnglOperator(Position, LHS, RHS);
	return N;
}

Statement* SnglOperator::Cut() //to be implemented
{
	Statement*N = new SnglOperator(Position, LHS, RHS);
	return N;
}

Statement* SnglOperator::Paste() //to be implemented
{
	Statement*N = new SnglOperator(Position, LHS, RHS);
	return N;
}
void SnglOperator::Move(Point &P) //to be implemented
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

void SnglOperator::Save(ofstream &OutFile)
{
	SplitRhs();
	bool succ = false;
	OutFile << Type << "\t" << ID << "\t" << Position.x << "\t" << Position.y << "\t" << LHS << "\tEQUAL\t";
	OutFile << Rhs.at(0) << '\t';
	switch(oper)
	{
	case '+':
		OutFile << "PLUS\t";
		break;
	case '-':
		OutFile << "MINUS\t";
		break;
	case '*':
		OutFile << "MULT\t";
		break;
	case '/':
		OutFile << "DIV\t";
		break;
	default:
		OutFile << "Invalid_operation";
	}
	OutFile << Rhs.at(1) << "\t" << Comment << "\n";
}

void SnglOperator::Load(ifstream &Infile) 
{
	string opName, temp_opr1, temp_opr2;
	Infile >> ID;
	Infile >> Position.x >> Position.y;
	Infile >> LHS;
	Infile.ignore(7);
	Infile >> temp_opr1;
	Rhs.push_back(temp_opr1);
	Infile >> opName;
	if (opName == "PLUS")
		oper = '+';
	else if (opName == "MINUS")
		oper = '-';
	else if (opName == "MULT")
		oper = '*';
	else if (opName == "DIV")
		oper = '/';
	else oper = NULL;

	Infile >> temp_opr2;
	Rhs.push_back(temp_opr2);
	RHS = temp_opr1 + oper + temp_opr2;
	getline(Infile, Comment);
	UpdateStatementText();
}

Statement* SnglOperator::GenerateCode(ofstream &OutFile)
{
	OutFile << "\t" << Text << ";\t" << "//" << Comment << "\n";
	return pConn->getDstStat();
}

void SnglOperator::ZoomIn(Output* & pOut) 
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

void SnglOperator::ZoomOut(Output* & pOut) 
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

bool SnglOperator::Valid(Output*pOut)
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

void SnglOperator::Simulate(vector<pair<string, double>>& variables, Input*pIn, Output*pOut)
{
	pair<bool, bool> check = checkType();

	if ((check.first && check.second) == true) // x + y
	{
		bool LHSexist = false;
		RHSexist1 = false;
		RHSexist2 = false;
		int LHSloc, RHSloc1, RHSloc2;

		for (int j = 0; j < variables.size(); j++)
		{
			if (Rhs.at(0) == variables.at(j).first)
			{
				RHSexist1 = true;
				RHSloc1 = j;
			}
			if (Rhs.at(1) == variables.at(j).first)
			{
				RHSexist2 = true;
				RHSloc2 = j;
			}
			if (RHSexist1 && RHSexist2) break;
		}

		for (int j = 0; j < variables.size(); j++)
		{
			if (LHS == variables.at(j).first)
			{
				LHSexist = true;
				LHSloc = j;
				break;
			}
		}

		if (!RHSexist1 && !RHSexist2)
		{
			pOut->PrintMessage("undefined right handside");
			return;
		}

		if (LHSexist)
		{
			switch (oper)
			{
			case '+':
				variables.at(LHSloc).second = variables.at(RHSloc1).second + variables.at(RHSloc2).second;
				return;
			case '-':
				variables.at(LHSloc).second = variables.at(RHSloc1).second - variables.at(RHSloc2).second;
				return;
			case '*':
				variables.at(LHSloc).second = variables.at(RHSloc1).second * variables.at(RHSloc2).second;
				return;
			case '/':
				variables.at(LHSloc).second = variables.at(RHSloc1).second / variables.at(RHSloc2).second;
				return;
			}

		}
		else
		{
			varNameVal.first = LHS;
			switch (oper)
			{
			case '+':
				varNameVal.second = variables.at(RHSloc1).second + variables.at(RHSloc2).second;
				variables.push_back(varNameVal);
				return;
			case '-':
				varNameVal.second = variables.at(RHSloc1).second - variables.at(RHSloc2).second;
				variables.push_back(varNameVal);
				return;
			case '*':
				varNameVal.second = variables.at(RHSloc1).second * variables.at(RHSloc2).second;
				variables.push_back(varNameVal);
				return;
			case '/':
				varNameVal.second = variables.at(RHSloc1).second / variables.at(RHSloc2).second;
				variables.push_back(varNameVal);
				return;
			}

		}
	}

	else if (check.first == true && check.second == false) // x + 3
	{
		bool LHSexist = false;
		RHSexist = false;
		int LHSloc, RHSloc;

		for (int j = 0; j < variables.size(); j++)
		{
			if (Rhs.at(0) == variables.at(j).first)
			{
				RHSexist = true;
				RHSloc = j;
				break;
			}
		}

		for (int j = 0; j < variables.size(); j++)
		{
			if (LHS == variables.at(j).first)
			{
				LHSexist = true;
				LHSloc = j;
				break;
			}
		}

		if (!RHSexist)
		{
			pOut->PrintMessage("undefined right handside");
			return;
		}

		if (LHSexist)
		{
			switch (oper)
			{
			case '+':
				variables.at(LHSloc).second = variables.at(RHSloc).second + stod(Rhs.at(1));
				return;
			case '-':
				variables.at(LHSloc).second = variables.at(RHSloc).second - stod(Rhs.at(1));
				return;
			case '*':
				variables.at(LHSloc).second = variables.at(RHSloc).second * stod(Rhs.at(1));
				return;
			case '/':
				variables.at(LHSloc).second = variables.at(RHSloc).second / stod(Rhs.at(1));
				return;
			}

		}
		else
		{
			varNameVal.first = LHS;
			switch (oper)
			{
			case '+':
				varNameVal.second = variables.at(RHSloc).second + stod(Rhs.at(1));
				variables.push_back(varNameVal);
				return;
			case '-':
				varNameVal.second = variables.at(RHSloc).second - stod(Rhs.at(1));
				variables.push_back(varNameVal);
				return;
			case '*':
				varNameVal.second = variables.at(RHSloc).second * stod(Rhs.at(1));
				variables.push_back(varNameVal);
				return;
			case '/':
				varNameVal.second = variables.at(RHSloc).second / stod(Rhs.at(1));
				variables.push_back(varNameVal);
				return;
			}

		}
	}

	if (check.first == false && check.second == true) // 3 + x
	{
		bool LHSexist = false;
		RHSexist = false;
		int LHSloc, RHSloc;

		for (int j = 0; j < variables.size(); j++)
		{
			if (Rhs.at(1) == variables.at(j).first)
			{
				RHSexist = true;
				RHSloc = j;
				break;
			}
		}

		for (int j = 0; j < variables.size(); j++)
		{
			if (LHS == variables.at(j).first)
			{
				LHSexist = true;
				LHSloc = j;
				break;
			}
		}

		if (!RHSexist)
		{
			pOut->PrintMessage("undefined right handside");
			return;
		}

		if (LHSexist)
		{
			switch (oper)
			{
			case '+':
				variables.at(LHSloc).second = variables.at(RHSloc).second + stod(Rhs.at(0));
				return;
			case '-':
				variables.at(LHSloc).second = variables.at(RHSloc).second - stod(Rhs.at(0));
				return;
			case '*':
				variables.at(LHSloc).second = variables.at(RHSloc).second * stod(Rhs.at(0));
				return;
			case '/':
				variables.at(LHSloc).second = variables.at(RHSloc).second / stod(Rhs.at(0));
				return;
			}

		}
		else
		{
			varNameVal.first = LHS;
			switch (oper)
			{
			case '+':
				varNameVal.second = variables.at(RHSloc).second + stod(Rhs.at(0));
				variables.push_back(varNameVal);
				return;
			case '-':
				varNameVal.second = variables.at(RHSloc).second - stod(Rhs.at(0));
				variables.push_back(varNameVal);
				return;
			case '*':
				varNameVal.second = variables.at(RHSloc).second * stod(Rhs.at(0));
				variables.push_back(varNameVal);
				return;
			case '/':
				varNameVal.second = variables.at(RHSloc).second / stod(Rhs.at(0));
				variables.push_back(varNameVal);
				return;
			}

		}
	}

	if ((check.first  && check.second) == false) // 3 + 5
	{
		bool LHSexist = false;
		int LHSloc;

		for (int j = 0; j < variables.size(); j++)
		{
			if (LHS == variables.at(j).first)
			{
				LHSexist = true;
				LHSloc = j;
				break;
			}
		}

		if (LHSexist)
		{
			switch (oper)
			{
			case '+':
				variables.at(LHSloc).second = stod(Rhs.at(0)) + stod(Rhs.at(1));
				return;
			case '-':
				variables.at(LHSloc).second = stod(Rhs.at(0)) - stod(Rhs.at(1));
				return;
			case '*':
				variables.at(LHSloc).second = stod(Rhs.at(0)) * stod(Rhs.at(1));
				return;
			case '/':
				variables.at(LHSloc).second = stod(Rhs.at(0)) / stod(Rhs.at(1));
				return;
			}

		}
		else
		{
			varNameVal.first = LHS;
			switch (oper)
			{
			case '+':
				varNameVal.second = stod(Rhs.at(0)) + stod(Rhs.at(1));
				variables.push_back(varNameVal);
				return;
			case '-':
				varNameVal.second = stod(Rhs.at(0)) - stod(Rhs.at(1));
				variables.push_back(varNameVal);
				return;
			case '*':
				varNameVal.second = stod(Rhs.at(0)) * stod(Rhs.at(1));
				variables.push_back(varNameVal);
				return;
			case '/':
				varNameVal.second = stod(Rhs.at(0)) / stod(Rhs.at(1));
				variables.push_back(varNameVal);
				return;
			}

		}

	}
}

void SnglOperator::watch(vector<pair<string, double>>& variables, Output* pout)
{
	ostringstream T;
	if (RHSexist1 && RHSexist2)
	{
		double x, y, z;
		for (int i = 0; i < variables.size(); i++)
		{
			if (LHS == variables.at(i).first)
				x = variables.at(i).second;
			if (Rhs.at(0) == variables.at(i).first)
				y = variables.at(i).second;
			if (Rhs.at(1) == variables.at(i).first)
				z = variables.at(i).second;
		}
		T << LHS << " = " << x << "\t";
		T << Rhs.at(0) << " = " << y << "\t";
		T << Rhs.at(1) << " = " << z;
	}
	pair<bool, bool> check = checkType();

	if ((check.first && check.second) == true)
	{
		if (!RHSexist1 || !RHSexist2)
		{
			T << LHS << " = ...";
			if (!RHSexist1)
			{
				T << Rhs.at(0) << " invalid	\t";
				if (RHSexist2)
				{
					for (int i = 0; i < variables.size(); i++)
					{
						if (Rhs.at(1) == variables.at(i).first)
							T << Rhs.at(1) << " = " << variables.at(i).second;
					}
				}
			}
			if (!RHSexist2)
			{
				T << Rhs.at(1) << " invalid	\t";
				if (RHSexist1)
				{
					for (int i = 0; i < variables.size(); i++)
					{
						if (Rhs.at(0) == variables.at(i).first)
							T << Rhs.at(0) << " = " << variables.at(i).second;
					}
				}
			}
		}
	}
	if (check.first == false && check.second == false)
	{
		for (int i = 0; i < variables.size(); i++)
		{
			if (LHS == variables.at(i).first)
				T << LHS << " = " << variables.at(i).second;
		}
	}
	if (check.first == true && check.second == false)
	{
		if (RHSexist)
		{
			for (int i = 0; i < variables.size(); i++)
			{
				if (LHS == variables.at(i).first)
					T << LHS << " = " << variables.at(i).second << "\t";
				if (Rhs.at(0) == variables.at(i).first)
					T << Rhs.at(0) << " = " << variables.at(i).second << "\t";
			}
		}
		else
		{
			T << LHS << " =....\t" << Rhs.at(0) << "invalid\t";
		}
	}
	if (check.first == false && check.second == true)
	{
		if (RHSexist)
		{
			for (int i = 0; i < variables.size(); i++)
			{
				if (LHS == variables.at(i).first)
					T << LHS << " = " << variables.at(i).second << "\t";
				if (Rhs.at(1) == variables.at(i).first)
					T << Rhs.at(1) << " = " << variables.at(i).second << "\t";
			}
		}
		else
		{
			T << LHS << " =....\t" << Rhs.at(1) << "invalid\t";
		}
	}
	string out = T.str();
	pout->PrintMessage(out);
	out = "";
}

void SnglOperator::deleteCon(Connector*c)
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
SnglOperator::~SnglOperator() //to be implemented
{}