#ifndef VAR_ASSIGN_H
#define VAR_ASSIGN_H

#include "Statement.h"

class VarAssign : public Statement
{
private:

	string LHS;
	string RHS;
	bool RHSexist;
	pair<string, double> varNameVal;

	int ASSGN_WDTH;
	int ASSGN_HI;

	Connector *pConn;
	Point Inlet;
	Point Outlet;

	virtual void UpdateStatementText();

public:

	VarAssign(Point Lcorner = 0 , string LeftHS = "", string RightHS = "");

	void setLHS(const string &L);
	void setRHS(const string &L);
	virtual string getLHS() { return LHS; }
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
	void watch(vector<pair<string, double>>& variables, Output* pout);

	~VarAssign();
};

#endif