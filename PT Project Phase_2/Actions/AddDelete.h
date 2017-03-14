#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

class Delete :public Action
{
private:
	Point position;
	Statement**Pointer;
	Connector**con;

public:

	Delete(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();

};