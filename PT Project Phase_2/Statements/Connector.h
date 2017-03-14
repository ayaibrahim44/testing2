#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "..\GUI\UI_Info.h"
#include "..\GUI\output.h"
#include "..\Statements\Statement.h"
class Statement;
class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	bool Selected;
public:
	Connector(Statement* Src, Statement* Dst);

	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	

	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();

	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	void Draw(Output* pOut) const;

	bool IsSelected();
	void setSelect(bool);
	bool InArea(Point) const;
	virtual void Edit(Statement*, Statement*);

	void Save(ofstream &Outfile);
	void Load(ifstream &Infile);	

	void ZoomIn();
	void ZoomOut();
};

#endif