#include "Condition.h"

Condition::Condition(Point Ucorner, string LeftHS, string operation)
{
	Position = Ucorner;
	LHS = LeftHS;

	OPERATION = operation;

	Position = Ucorner;

	pConnTrue = NULL;	//No connectors yet
	pConnFalse = NULL;
}

void Condition::setBranch(bool t)
{
	Branch = t;
}

int Condition::getBranch()
{
	if (Branch == true)
		return 1;
	else return 2;
}

void Condition::setConnector(Connector* conn)
{
	if (Branch == true)
		pConnTrue = conn;
	else pConnFalse = conn;
}

void Condition::setToConnector(Connector* C)
{
	toConnect[toCon] = C;
	toCon++;
}

Connector* Condition::getConnector()
{
	if (Branch == true)
		return pConnTrue;
	else return pConnFalse;
}
Connector* Condition::getTBranch()
{
	return pConnTrue;
}
Connector* Condition::getFBranch()
{
	return pConnFalse;
}
void Condition::Draw(Output* pOut) const
{
	pOut->DrawCondition(Position, COND_DIAG1, COND_DIAG2, Text, Selected);
}

bool Condition::InArea(Point P) const
{
	Point Center, Left, Right, Down;
	Center.x = Position.x;
	Center.y = Position.y + COND_DIAG1 / 2;

	Left.x = Position.x - (COND_DIAG2 / 2);
	Left.y = Position.y + (COND_DIAG1 / 2);

	Right.x = Position.x + (COND_DIAG2 / 2);
	Right.y = Position.y + (COND_DIAG1 / 2);

	Down.x = Position.x;
	Down.y = Position.y + COND_DIAG1;

	Point U, V, W;
	U.x = (Right.x - Left.x) / COND_DIAG2;
	U.y = (Right.y - Left.y) / COND_DIAG2;

	V.x = (Down.x - Position.x) / COND_DIAG1;
	V.y = (Down.y - Position.y) / COND_DIAG1;

	W.x = P.x - Center.x;
	W.y = P.y - Center.y;

	double xabs = abs(W.x*U.x + W.y*U.y);
	double yabs = abs(W.x*V.x + W.y*V.y);

	if ((2 * xabs / COND_DIAG2) + (2 * yabs / COND_DIAG1) <= 1)
		return true;
	else return false;

}

bool Condition::InFirstHalf(Point P) const
{
	if (InArea(P))
	{
		if (P.x < Position.x)
			return true;
		return false;
	}
	return false;
}

Point Condition::getInlet() const
{
	return Inlet;
}

Point Condition::getOutlet() const
{
	if (Branch == true)
		return OutletTrue;
	return OutletFalse;
}

void Condition::Move(Point&P) //to be implemented
{
	Position = P;

	Inlet.x = Position.x;
	Inlet.y = Position.y;

	OutletTrue.x = Position.x - (COND_DIAG2 / 2);
	OutletFalse.x = Position.x + (COND_DIAG2 / 2);

	OutletTrue.y = Position.y + (COND_DIAG1 / 2);
	OutletFalse.y = Position.y + (COND_DIAG1 / 2);
	if (pConnTrue != NULL)
		pConnTrue->setStartPoint(OutletTrue);
	if (pConnFalse != NULL)
		pConnFalse->setStartPoint(OutletFalse);
	if (toCon != 0);
	for (int i = 0; i<toCon; i++)
	{
		toConnect[i]->setEndPoint(getInlet());
	}
}

void Condition::setComment() //to be implemented
{}

void Condition::ZoomIn(Output* & pOut)
{
	font *= 1.2;
	pOut->setFont(font);
	COND_DIAG1 *= 1.2;
	COND_DIAG2 *= 1.2;
	Inlet.x = Position.x;
	Inlet.y = Position.y;

	OutletTrue.x = Position.x - (COND_DIAG2 / 2);
	OutletFalse.x = Position.x + (COND_DIAG2 / 2);

	OutletTrue.y = Position.y + (COND_DIAG1 / 2);
	OutletFalse.y = Position.y + (COND_DIAG1 / 2);
}

void Condition::ZoomOut(Output* & pOut)
{
	font /= 1.2;
	pOut->setFont(font);
	COND_DIAG1 /= 1.2;
	COND_DIAG2 /= 1.2;
	Inlet.x = Position.x;
	Inlet.y = Position.y;

	OutletTrue.x = Position.x - (COND_DIAG2 / 2);
	OutletFalse.x = Position.x + (COND_DIAG2 / 2);

	OutletTrue.y = Position.y + (COND_DIAG1 / 2);
	OutletFalse.y = Position.y + (COND_DIAG1 / 2);
}

relationalOperators Condition::getOperator(string oper)
{
	if (oper == "==")
		return IsEqual;
	if (oper == "!=")
		return NotEqual;
	if (oper == "<")
		return Lessthan;
	if (oper == "<=")
		return LessthanOrEqual;
	if (oper == ">")
		return Greaterthan;
	if (oper == ">=")
		return GreaterthanOrEqual;
	return NoOperation;
}

void Condition::deleteCon(Connector*c)
{
	if (c == pConnTrue)
		pConnTrue = NULL;
	else if (c == pConnFalse)
		pConnFalse = NULL;
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
Condition::~Condition() //to be implemented
{}