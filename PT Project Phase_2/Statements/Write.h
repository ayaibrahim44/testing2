#ifndef WRITE_H
#define WRITE_H

#include "Statement.h"

class Write : public Statement
{
private:

	string varName;
	Connector *pConn;
	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	int WRITE_WDTH;
	int WRITE_HI;

	virtual void UpdateStatementText();

public:
	Write(Point Lcorner = 0, string N = "");
	void setname(const string &N);
	virtual string getLHS() { return varName; }
	virtual Connector* getConnector();
	virtual void setConnector(Connector*);
	virtual void setToConnector(Connector*);
	virtual void deleteCon(Connector*);

	virtual void Draw(Output* pOut) const;
	virtual bool InArea(Point) const;
	virtual Point getInlet() const;
	virtual Point getOutlet() const;

	virtual void Edit(Output*,Input*);
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
	void watch(vector<pair<string, double>>& variables, Output* pout) {}

	~Write();
};

#endif