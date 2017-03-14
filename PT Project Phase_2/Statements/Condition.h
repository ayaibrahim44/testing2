#ifndef CONDITION_STATEMENT
#define CONDITION_STATEMENT

#include "Statement.h"
#include<sstream>

class Condition : public Statement
{
protected:

	string LHS;	//Left Handside of the condition statement (name of a variable)

	string OPERATION; //relation between LHS and RHS

	int COND_DIAG1; //diagonal length
	int COND_DIAG2; //diagonal length

	Connector *pConnTrue;
	Connector *pConnFalse;

	Point Inlet;	//A point where connections enters this statement 
	Point OutletTrue;	//two points the connections leave this statement
	Point OutletFalse;

	bool Branch;
	virtual void UpdateStatementText() = 0;
	relationalOperators getOperator(string oper);

public:

	Condition(Point Upcorner = 0, string LeftHS = "", string Oper = "=");

	virtual void setBlock(Statement*) = 0;
	virtual Statement* getEndBlock() = 0;
	virtual void initializeBlocks() = 0;

	virtual void setBranch(bool);
	virtual int getBranch();

	virtual Connector* getConnector();
	virtual void setConnector(Connector*);
	virtual void setToConnector(Connector*);
	virtual void deleteCon(Connector*);

	Connector* getTBranch();
	Connector* getFBranch();


	virtual void Draw(Output* pOut) const;
	virtual bool InArea(Point) const;
	virtual bool InFirstHalf(Point) const;
	virtual Point getInlet() const;
	virtual Point getOutlet() const;

	virtual void Edit(Output*,Input*) = 0;
	virtual void Move(Point &P);
	virtual void setComment();

	//virtual void setTrueFalseB();
	//virtual Statement* getTrueFalseB();

	virtual Statement* Copy() = 0;
	virtual Statement* Cut() = 0;
	virtual Statement* Paste() = 0;

	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file

	virtual void ZoomIn(Output* & pOut);
	virtual void ZoomOut(Output* & pOut);

	virtual Statement* GenerateCode(ofstream &OutFile) = 0;
	virtual void Simulate(vector<pair<string, double>>&, Input*, Output*) = 0;
	void watch(vector<pair<string, double>>& variables, Output* pout){}

	virtual ~Condition();
};

#endif