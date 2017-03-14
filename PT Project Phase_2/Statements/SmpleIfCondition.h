#ifndef SMPLE_IF_CONDITION_STATEMENT
#define SMPLE_IF_CONDITION_STATEMENT

#include "Condition.h"

class SmpleIfCondition : public Condition
{
	double RHS;
	virtual void UpdateStatementText();
	vector<Statement*> TrueBlock;
	vector<Statement*> FalseBlock;
	Statement* Endif;
	bool valid;
public:

	SmpleIfCondition(Point Upcorner = 0, string LeftHS = "", double RightHS = 0.0, string Oper = "=");

	void setLHS(const string &L);
	void setOperat(const string&);
	void setRHS(const double R);

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
	~SmpleIfCondition();
};

#endif