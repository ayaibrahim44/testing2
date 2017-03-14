#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
	int font;
public:

	//Default constructor
	Output();	

	//create the window 
	window* CreateWind(int, int, int , int);
	//creates a pointer to the Input object
	Input* CreateInput();

	void setFont(int);

	// -- Adjust the interface

	//create functions
	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar();//Tool bar of the simulation mode
	void ClearStatusBar();

	// -- Statements Drawing Functions

	//Start_End Drawing Function
	void DrawStartEnd(Point Left, int width, int height, string Text, bool Selected);

	//Read drawing function
	void DrawReadWrite(Point Left, int width, int length, string Text, bool Selected = false);

	//Assignment statements
	void DrawAssign(Point Left, int width, int height, string Text, bool Selected=false);

	//Conditional Drawing Function
	void DrawCondition(Point Up, int Diag1, int Diag2, string Text, bool Selected=false);

	//Draw a connector

	//Draw Arrowhead -> get the two points
	void calcVertexes(Point Start, Point End, double&x1, double&y1, double&x2, double&y2);
	//Draw the connector with an arrow head
	void DrawConnector(Point Src, Point Dst, bool Selected = false);
	void DrawBentConnector(Point Src, Point Dst, bool Selected = false);
	//Print a message on Status bar
	void PrintMessage(string msg);	

	//Destructor
	~Output();
};

#endif