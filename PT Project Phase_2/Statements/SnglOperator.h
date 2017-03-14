
#ifndef SNGL_OPERATOR_H
#define SNGL_OPERATOR_H

#include "Statement.h"
#include <vector>

class SnglOperator : public Statement
{
	string LHS;
	string RHS;
	bool RHSexist1;
	bool RHSexist2;
	bool RHSexist;
	pair<string, double> varNameVal;

	int ASSGN_WDTH;
	int ASSGN_HI;

	vector<string> Rhs;
	pair<bool, bool>checkType();
	char oper;

	Connector *pConn;

	Point Inlet;
	Point Outlet;
	void SplitRhs();
	virtual void UpdateStatementText();

public:
	SnglOperator(Point Lcorner = 0 , string LeftHS = "", string Right = "");

	void setLHS(const string &L);
	void setRHS(const string &R);
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

	~SnglOperator();
};

#endif