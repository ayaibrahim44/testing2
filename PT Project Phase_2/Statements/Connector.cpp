#include "Connector.h"

Connector::Connector(Statement* Src, Statement* Dst)	
//When a connector is created, it must have a source statement and a destination statement
//There are no free connectors in the folwchart
{
	Selected = false;
	SrcStat = Src;
	DstStat = Dst;
}

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint()
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}

void Connector::Draw(Output* pOut) const
{
	pOut->DrawConnector(Start, End, Selected);
}

void Connector::Save(ofstream &Outfile)
{
	if (SrcStat->getType() == "SMPL_IFCONDITION" || SrcStat->getType() == "VAR_IFCONDITION"
		|| SrcStat->getType() == "SMPL_WHILELOOP" || SrcStat->getType() == "VAR_WHILELOOP")
	{
		if (SrcStat->InFirstHalf(Start))
			SrcStat->setBranch(true);
		else SrcStat->setBranch(false);
	}
	Outfile << SrcStat->getID() << "\t" << DstStat->getID() << "\t" << SrcStat->getBranch() << "\n";
}
void Connector::Load(ifstream &Infile)
{
	int branch;
	Infile >> branch;
	if (branch == 1)
		SrcStat->setBranch(true);
	else if (branch == 2)
		SrcStat->setBranch(false);

	Start = SrcStat->getOutlet();
	End = DstStat->getInlet();
	SrcStat->setConnector(this);
}

void Connector::ZoomIn()
{
	if (SrcStat->getType() == "SMPL_IFCONDITION" || SrcStat->getType() == "VAR_IFCONDITION"
		|| SrcStat->getType() == "SMPL_WHILELOOP" || SrcStat->getType() == "VAR_WHILELOOP")
	{
		SrcStat->setBranch(true);
		if (SrcStat->getConnector() == this);
		else SrcStat->setBranch(false);
	}
	setStartPoint(SrcStat->getOutlet());
	setEndPoint(DstStat->getInlet());
}

void Connector::ZoomOut()
{
	if(SrcStat->getType() == "SMPL_IFCONDITION" || SrcStat->getType() == "VAR_IFCONDITION"
		|| SrcStat->getType() == "SMPL_WHILELOOP" || SrcStat->getType() == "VAR_WHILELOOP")
	{
		SrcStat->setBranch(true);
		if (SrcStat->getConnector() == this);
		else SrcStat->setBranch(false);
	}
	setStartPoint(SrcStat->getOutlet());
	setEndPoint(DstStat->getInlet());
}

bool Connector::InArea(Point P) const
{
	if (Start.x != End.x)
	{
		float m = float(Start.y - End.y) / float(Start.x - End.x);
		float a = P.y - Start.y;
		float b = m* (P.x - Start.x);
		if (Start.x < End.x)
		{
			if (P.x > Start.x && P.x < End.x)
			{
				if (Start.y < End.y)
				{
					if (P.y > Start.y && P.y < End.y)
						return (b - a <= 4 && b - a >= -4);
				}
				else
				{
					if (P.y > End.y && P.y < Start.y)
						return (b - a <= 4 && b - a >= -4);
				}
			}
		}
		else
		{
			if (P.x > End.x && P.x < Start.x)
			{
				if (Start.y < End.y)
				{
					if (P.y > Start.y && P.y < End.y)
						return (b - a <= 4 && b - a >= -4);
				}
				else
				{
					if (P.y > End.y && P.y < Start.y)
						return (b - a <= 4 && b - a >= -4);
				}
			}
		}
	}
	else
	{
		if (P.x - Start.x <= 4 && P.x - Start.x >= -4)
			return (P.y >= Start.y && P.y <= End.y);
	}
	return false;
}

void Connector::Edit(Statement* s, Statement* d)
{
	SrcStat->deleteCon(this);
	DstStat->deleteCon(this);
	SrcStat = s;
	DstStat = d;
	SrcStat->setConnector(this);
	DstStat->setToConnector(this);
	Start = SrcStat->getOutlet();
	End = DstStat->getInlet();
}

bool Connector::IsSelected()
{
	return Selected;
}

void Connector::setSelect(bool b)
{
	Selected = b;
}