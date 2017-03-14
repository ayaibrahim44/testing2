#ifndef VAR_IF_CONDITION_STATEMENT
#define VAR_IF_CONDITION_STATEMENT

#include "Condition.h"

class VarIfCondition : public Condition
{
	string RHS;
	bool LHSexist ;
	bool RHSexist ;
	virtual void UpdateStatementText();
	vector<Statement*> TrueBlock;
	vector<Statement*> FalseBlock;
	Statement* Endif;
	bool valid;

public:
	VarIfCondition(Point Upcorner = 0, string LeftHS = "", string RightHS = "", string Oper = "=");

	void setLHS(const string &L);
	void setOperat(const string &O);
	void setRHS(const string &R);

	void setBlock(Statement*);
	Statement* getEndBlock(){ return Endif; }
	void initializeBlocks(){ Endif = 0; TrueBlock.clear(); FalseBlock.clear(); }

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


	~VarIfCondition();
};

#endif