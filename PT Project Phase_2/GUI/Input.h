#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output; //Forward declaration

class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
public:

	//Consturctor
	Input(window *pW);

	// -- Get Functions
	//Get coordinate where user clicks
	void GetPointClicked(Point &P) const;

	//Returns a string entered by the user
	string GetString(Output* pO) const;

	void GetVar(Output* pO, string& sv, double& dv);

	string GetOperation(Output* pO) const;

	// Reads a double value from the user 
	double GetValue(Output* pO) const;

	void ReadStat(Output* pO, string& variable1, string& operation, string& variable2, double& var2);
	string ReadExpression(Output* pO);

	char GetCharOper(Output* pO) const;

	//Read the user click and map it to an action
	ActionType GetUserAction() const; 

	//Destructor
	~Input();
};

#endif