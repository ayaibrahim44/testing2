#ifndef VAR_WHILE_LOOP_STATEMENT
#define VAR_WHILE_LOOP_STATEMENT

#include "Condition.h"

class VarWhileLoop : public Condition
{
	string RHS;
	bool LHSexist ;
	bool RHSexist;
	virtual void UpdateStatementText();
	Statement* EndLoop;
	vector<Statement*> loop;
	bool direction;
	bool valid;
public:
	VarWhileLoop(Point Upcorner = 0, string LeftHS = "", string RightHS = "", string Oper = "=");

	void setLHS(const string &L);
	void setOperat(const string &O);
	void setRHS(const string &R);

	virtual void setBlock(Statement*);
	virtual Statement* getEndBlock(){ return EndLoop; }
	virtual void initializeBlocks(){ EndLoop = NULL; loop.clear(); }


	virtual void Edit(Output*,Input*);

	virtual Statement* Copy();
	virtual Statement* Cut();
	virtual Statement* Paste();

	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);

	virtual Statement* GenerateCode(ofstream &OutFile);
	virtual void Simulate(vector<pair<string, double>>&, Input*, Output*);
	void watch(vector<pair<string, double>>& variables, Output* pout);

	virtual bool Valid(Output*);

	~VarWhileLoop();
};

#endif