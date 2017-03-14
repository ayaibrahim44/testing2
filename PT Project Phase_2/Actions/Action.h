#ifndef ACTION_H
#define ACTION_H

#include "..\GUI\UI_Info.h"

class ApplicationManager; 
class Input;
class Output;

//forward class declaration

/*Reduce the number of #include files in header files. 
It will reduce build times. 
Instead, put include files in source code files and use forward declarations in header files.
If a class in a header file does not need to know the size of a data member class 
or does not need to use the class's members then forward declare the class instead of including the file with #include.
To avoid the need of a full class declaration, use references (or pointers) and forward declare the class. */



//Base class for all possible actions

class Action
{
protected:
	
	//Pointer to ApplicationManager because action needs this pointer for its functions
	ApplicationManager *pManager;	
public:

	Action(ApplicationManager *pAppManager) 
	{ pManager = pAppManager; }
	
	//pure virtual function
	//can't be called for the base class "Action" but for a derived class

	//Reads parameters required for action to execute
	virtual void ReadActionParameters() =0;
	
	//Execute action (code depends on action type)
	virtual void Execute() =0;
};

#endif