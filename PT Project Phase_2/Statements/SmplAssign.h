#ifndef SMPL_ASSIGN_H
#define SMPL_ASSIGN_H

#include "Statement.h"

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value

class SmplAssign : public Statement
{
private:

	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)

	int ASSGN_WDTH;
	int ASSGN_HI;

	pair<string, double> varNameVal;

	Connector *pConn;	//Simple Assignment Stat. has one Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	virtual void UpdateStatementText();

public:
	SmplAssign(Point Lcorner = 0, string LeftHS = "", double RightHS = 0);
	
	void setLHS(string &L);
	void setRHS(double R);
	virtual string getLHS() { return LHS; }
	virtual Connector* getConnector();
	virtual void setConnector(Connector*);
	virtual void setToConnector(Connector*);
	virtual void deleteCon(Connector*);

	virtual void Draw(Output* pOut) const;
	virtual bool InArea(Point) const;
	virtual Point getInlet() const;
	virtual Point getOutlet() const;

	virtual void Edit(Output* , Input* );
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
	~SmplAssign();
};

#endif