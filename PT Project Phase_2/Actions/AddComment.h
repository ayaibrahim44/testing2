#include "..\Statements\SmplAssign.h"
#include"Action.h"

class Comment :public Action
{
	string comment;
	Statement*SelStat;

public:
	Comment(ApplicationManager *pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();

};