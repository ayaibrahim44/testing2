#ifndef END_H
#define END_H

#include "Statement.h"

class End : public Statement
{
	Point Inlet;	//A point a connection leaves this statement
	virtual void UpdateStatementText();
public:
	End(Point Lcorner = 0);

	virtual void setConnector(Connector*){}
	virtual void setToConnector(Connector*);
	virtual Connector* getConnector(){ return NULL; }
	virtual void deleteCon(Connector*);

	virtual void Draw(Output* pOut) const;
	virtual bool InArea(Point) const;
	virtual Point getInlet() const;
	virtual Point getOutlet() const { return 0; }

	virtual void Edit(Output*, Input*);
	virtual void Move(Point &P);
	virtual void setComment();

	virtual Statement* Copy();
	virtual Statement* Cut();
	virtual Statement* Paste();

	virtual void Save(ofstream &OutFile);	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile);	//Load the Statement parameters from a file

	virtual void ZoomIn(Output* & pOut);
	virtual void ZoomOut(Output* & pOut);

	virtual bool Valid(Output*);
	virtual Statement* GenerateCode(ofstream &OutFile);
	virtual void Simulate(vector<pair<string, double>>&, Input*, Output*);
	void watch(vector<pair<string, double>>& variables, Output* pout);

	~End();
};

#endif