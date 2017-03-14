#ifndef ADD_IF_CONDITION_H
#define ADD_IF_CONDITION_H

#include "Action.h"
#include "..\Statements\SmpleIfCondition.h"
#include "..\Statements\VarIfCondition.h"

//Add Condition Statement Action
//This class is responsible for 
// 1 - Getting Condition stat. coordinates from the user
// 2 - Creating an object of Condition class and fill it parameters
// 3 - Adding the created object to the list of statements

class AddIfCondition : public Action
{
private:
	bool check;
	Point Position;	//Position where the user clicks to add the stat.
	string Variable1;
	string Variable2;
	double Var2;
	string operation;
public:
	AddIfCondition(ApplicationManager *pAppManager);

	//Read condition statements position
	virtual void ReadActionParameters();

	//Create and add a condition statement to the list of statements
	virtual void Execute();

};

#endif