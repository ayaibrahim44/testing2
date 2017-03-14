#ifndef SMPLE_WHILE_LOOP_STATEMENT
#define SMPLE_WHILE_LOOP_STATEMENT

#include "Condition.h"

class SmpleWhileLoop : public Condition
{
	double RHS;
	virtual void UpdateStatementText();
	Statement* EndLoop;
	vector<Statement*> loop;
	bool direction;
	bool valid;
public:

	SmpleWhileLoop(Point Upcorner = 0, string LeftHS = "", double RightHS = 0.0, string Oper = "=");

	void setLHS(const string &L);
	void setOperat(const string&);
	void setRHS(const double R);

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

	~SmpleWhileLoop();
};

#endif