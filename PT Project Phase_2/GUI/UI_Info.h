#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\DEFS.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)
	
	int width, height;	//Window width and height
	int wx, wy;			//Window starting coordinates

	int StBrWdth;		//Status Bar Width

	int HorTlBrWdth;	//Tool Bar Width
	int VerTlBrWdth;
	
	int MnItWdth;

	color DrawClr;		//Drawing color
	color HiClr;		//Highlighting color
	color MsgClr;		//Messages color

	int START_END_WDTH;
	int START_END_HI;

}UI;	//create a single global object UI

struct Point	
{
	int x,y;
	Point(int a=0, int b=0)	//constructor
	{ x=a;	y=b;	}
	bool operator==(Point& P)
	{
		if (x == P.x&&y == P.y)
			return true;
		else return false;
	}
};

#endif