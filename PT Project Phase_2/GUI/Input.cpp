#include "Input.h"
#include "Output.h"
#include <sstream>
//Construcor
Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

// -- Get Functions
//Get coordinate where user clicks
void Input::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

//determine while runtime whether the user enter a string or a double
void Input::GetVar(Output* pO, string& Str, double& D)
{
	Str = "";
	D = 0.0;
	char Key;
	pWind->WaitKeyPress(Key);
	Str += Key;
	pO->PrintMessage(Str);

	if (Key >= 45 && Key < 58 && Key != 47)
	{
		while (1)
		{
			pWind->WaitKeyPress(Key);
			if (Key == 27)	//ESCAPE key is pressed
				return;	//returns nothing as user has cancelled label
			if (Key == 13 || Key == 32)	//ENTER key is pressed
				break;
			if (Key == 8 && Str.size() != 0)	//BackSpace is pressed
			{
				Str.resize(Str.size() - 1);
				pO->PrintMessage(Str);
				if (Str.size() == 0)
				{
					GetVar(pO, Str, D);
					return;
				}
			}
			if (Key >= 45 && Key < 58 && Key != 47 && Str.size() <= 10)
				Str += Key;
			pO->PrintMessage(Str);
		}
		D = stod(Str.c_str());
		Str = "";
		return;
	}
	if ((Key >= 65 && Key <= 90) || (Key >= 97 && Key <= 122))
	{
		while (1)
		{
			pWind->WaitKeyPress(Key);
			if (Key == 27)	//ESCAPE key is pressed
				return;	//returns nothing as user has cancelled label
			if (Key == 13 || Key == 32)	//ENTER key is pressed
				break;
			if (Key == 8 && Str.size() != 0)	//BackSpace is pressed
			{
				Str.resize(Str.size() - 1);
				pO->PrintMessage(Str);
				if (Str.size() == 0)
				{
					GetVar(pO, Str, D);
					return;
				}
			}
			else if ((Key >= 65 && Key <= 90) || (Key >= 97 && Key <= 122) || (Key >= 48 && Key <= 57)
				&& Str.size() <= 10) //alphanumeric
				Str += Key;
			pO->PrintMessage(Str);
		}
		return;
	}
	GetVar(pO, Str, D);
}

//Returns a string entered by the user
string Input::GetString(Output *pO) const  //alphanumeric 
{
	string Str;
	char Key;

	pWind->WaitKeyPress(Key);
	if ((Key >= 65 && Key <= 90) || (Key >= 97 && Key <= 122))
	{
		Str += Key;
		pO->PrintMessage(Str);
	}
	else return Str = GetString(pO);

	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13 || Key == 32)	//ENTER key is pressed
			return Str;
		if (Key == 8 && Str.size() != 0)	//BackSpace is pressed
		{
			Str.resize(Str.size() - 1);
			pO->PrintMessage(Str);
			if (Str.size() == 0)
				return Str = GetString(pO);
		}
		else if ((Key >= 65 && Key <= 90) || (Key >= 97 && Key <= 122) || (Key >= 48 && Key <= 57)
			&& Str.size() <= 10) //alphanumeric
			Str += Key;
		pO->PrintMessage(Str);
	}
	return Str;
}

// Reads a double value from the user 
double Input::GetValue(Output* pO) const
{
	string Number;
	char Key;
	double D;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return NULL;	//returns nothing as user has cancelled label
		if (Key == 13 || Key == 32)	//ENTER key is pressed
			break;
		if (Key == 8 && Number.size() != 0)	//BackSpace is pressed
			Number.resize(Number.size() - 1);
		if (Key >= 45 && Key < 58 && Key != 47 && Number.size() <= 10)
			Number += Key;
		pO->PrintMessage(Number);
	}

	D = atof(Number.c_str());
	return D;
}

//read the conditional statement and determine simple/variable while runtime
void Input::ReadStat(Output* pO, string& variable1, string& operation, string& variable2, double& var2)
{
	pO->PrintMessage("LHS= ");
	variable1 = GetString(pO);
	pO->PrintMessage("Enter an operation");
	operation = GetOperation(pO);
	while (operation == ""){ pO->PrintMessage("Please enter a valid operation"); operation = GetOperation(pO); }
	string s_temp;
	double d_temp;
	pO->PrintMessage("RHS= ");
	GetVar(pO, s_temp, d_temp);
	variable2 = s_temp;
	var2 = d_temp;
}

//get the coditional operation
string Input::GetOperation(Output* pO) const
{
	string Str;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13 || Key == 32)	//ENTER key is pressed
			return Str;
		if (Key == 8 && Str.size() != 0)	//BackSpace is pressed
		{
			Str.resize(Str.size() - 1);
		}
		if ((Key == 33 || (Key >= 60 && Key <= 62)) && Str.size() < 2)
		{
			Str += Key;
		}
		pO->PrintMessage(Str);
	}
	return Str;
}

//get the single operator 
char Input::GetCharOper(Output* pO) const
{
	char Key;
	pWind->WaitKeyPress(Key);
	string temp = "";
	temp += Key;
	if (Key == '+' || Key == '-' || Key == '*' || Key == '/')
		pO->PrintMessage(temp);
	while (1)
	{
		if (Key == '+' || Key == '-' || Key == '*' || Key == '/')
			return Key;
		pO->PrintMessage("please enter a valid operator (+,-,*,/)");
		Key = GetCharOper(pO);
	}

}

//read the single operator RHS expression
string Input::ReadExpression(Output* pO)
{
	string op1, op2;
	double opr1, opr2;
	ostringstream T;
	GetVar(pO, op1, opr1);
	char operation = GetCharOper(pO);
	GetVar(pO, op2, opr2);

	if (op1 == "" && opr1 != 0 || (op1 == "" && opr1 == 0))
		T << opr1;
	else if (op1 != "" && opr1 == 0)
		T << op1;

	T <<" "<< operation<<" ";

	if (op2 == "" && opr2 != 0 || (op2 == "" && opr2 == 0))
		T << opr2;
	else if (op2 != "" && opr2 == 0)
		T << op2;

	string variable2 = T.str();
	return variable2;
}

//Read the user click and map it to an action
ActionType Input::GetUserAction() const
{	
	//This function reads the position where the user clicks to determine the desired action

	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the horizontal Toolbar
		if ( y >= 0 && y < UI.HorTlBrWdth)
		{	//Check whick Menu item was clicked
			if (x >= 0 && x < 90)return ADD_START;
			if (x < 180)return ADD_END;
			if (x < 270)return ADD_READ;
			if (x < 370)return ADD_WRITE;
			if (x < 450)return ADD_SMPL_ASSIGN;
			if (x < 530)return ADD_VAR_ASSIGN;
			if (x < 600)return ADD_SNGL_OPERAT;
			if (x < 670)return ADD_IF_CONDITION;
			if (x < 750)return ADD_WHILE_LOOP;
			if (x < 855)return ADD_CONNECTOR;
			if (x < 960)return SAVE;
			if (x < 1060)return LOAD;
			if (x < 1255)return SIM_MODE;
			if (x < 1365)return EXIT;
			return DSN_TOOL;	//a click on empty part of the tool bar
		}
		
		//[2] If user clicks on the vertical Toolbar
		if (y >= 100 && y < UI.height && x >= UI.width - UI.VerTlBrWdth && x <= UI.width)
		{
			//Check whick Menu item was clicked
			if (y >= 100 && y < 180)
				return EDIT_STAT;
			if (y < 245)
				return DEL;
			if (y < 300)
				return ZOOM_IN;
			if ( y < 360)
				return ZOOM_OUT;
			if (y < 420)
				return COPY;
			if (y < 480)
				return CUT;
			if (y < 555)
				return PASTE;
			if (y < 630)
				return MOVE;
			if (y < 690)
				return COMMENT;
		}
		//[2] User clicks on the drawing area
		if (y >= UI.HorTlBrWdth && y < UI.height - UI.StBrWdth && x >= 0 && x <= UI.width - UI.VerTlBrWdth)
		{
			return SELECT;	//user want to select/unselect a statement in the flowchart
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//Application is in Simulation mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.HorTlBrWdth)
		{	//Check whick Menu item was clicked
			if (x >= 0 && x < 275)
				return VALIDATE;
			if (x >= 275 && x < 523)
				return RUN;
			if (x >= 523 && x < 773)
				return STEP;
			if (x >= 773 && x < 1077)
				return CODE;
			if (x >= 1077 && x < UI.width)
				return DSN_MODE;
		}
		if (y >= UI.HorTlBrWdth && y < UI.height - UI.StBrWdth && x >= 0 && x <= UI.width - UI.VerTlBrWdth)
		{

			return DRAW_AREA;	//user want to select/unselect a statement in the flowchart
		}
		return STATUS;
	}

}

//Destructor
Input::~Input()
{
}
