#ifndef ADD_PASTE_H
#define ADD_PASTE_H
#include"Action.h"

class AddPaste :public Action
{
private:
	Point Position;
	string Text;
	string Type;
public:
	AddPaste(ApplicationManager *pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();

};
#endif
