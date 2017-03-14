#include "Output.h"

//Constructor
Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1365;
	UI.height = 745;
	UI.wx = 0;
	UI.wy =0;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StBrWdth = 65; //status bar width

	UI.MnItWdth = 100;
	
	// Design tool bar components

	UI.HorTlBrWdth = 100; //horizontal tool bar width
	UI.VerTlBrWdth = 80;

	UI.DrawClr = GOLD;
	UI.HiClr = RED;
	UI.MsgClr = GOLD;

	UI.START_END_WDTH= 100;
	UI.START_END_HI= 50;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");
	
	font = 25;

	pWind->SetPen(RED,3);
	CreateDesignToolBar();
}

//create the window 
window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//creates a pointer to the Input object
Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//


// CREATE FUNCTIONS

void Output::CreateDesignToolBar()
{
	UI.AppMode = DESIGN;	//Design Mode
	pWind->DrawImage("images\\project_final_design.jpg", 0, 0);
}

void Output::CreateSimulationToolBar()
{
	UI.AppMode = SIMULATION;	//Simulation Mode
	pWind->DrawImage("images\\SimMode.jpg", 0, 0);
}

void Output::ClearStatusBar()
{
	pWind->DrawImage("images\\StatusBar.jpg", 0, UI.height - UI.StBrWdth);
}

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//


//Draw Start and End
void Output::DrawStartEnd(Point Left, int width, int height, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawEllipse(Left.x, Left.y, Left.x + width, Left.y + height, FRAME);

	//Write statement text
	pWind->SetPen(WHITE, 2);
	pWind->SetFont(font, BOLD, BY_NAME, "Lucida Handwriting");
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);

}

//Draw Read statement
void Output::DrawReadWrite(Point Left, int length, int width, string Text, bool Selected)
{
	int ipX[] = { Left.x, Left.x + width / 2, Left.x + width / 2 + length, Left.x + length };
	int ipY[] = { Left.y, Left.y - width, Left.y - width, Left.y };
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color
	//Draw the statement block rhombus
	pWind->DrawPolygon(ipX, ipY, 4, FRAME);

	//Write statement text
	pWind->SetPen(WHITE, 2);
	pWind->SetFont(font, BOLD, BY_NAME, "Lucida Handwriting");
	pWind->DrawString(Left.x + length / 6, Left.y - width / 2 - 10, Text);
}

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point Left, int width, int height, string Text, bool Selected)
{
	if(Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr,3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr,3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height,FRAME);
		
	//Write statement text
	pWind->SetPen(WHITE, 2);
	pWind->SetFont(font, BOLD, BY_NAME, "Lucida Handwriting");
	pWind->DrawString(Left.x + width / 16, Left.y + height / 4, Text);
}

//Draw conditional statement and write the "Text" on it
void Output::DrawCondition(Point Up, int Diag1, int Diag2, string Text, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color

	int ipX[] = { Up.x - (Diag2 / 2), Up.x, Up.x + (Diag2 / 2), Up.x };
	int ipY[] = { Up.y + (Diag1 / 2), Up.y, Up.y + (Diag1 / 2), Up.y + Diag1 };
	
	//Draw the statement block rhombus
	pWind->DrawPolygon(ipX, ipY, 4, FRAME);


	//Write statement text
	pWind->SetPen(WHITE, 2);
	pWind->SetFont(font, BOLD, BY_NAME, "Lucida Handwriting");
	pWind->DrawString(Up.x - 2* Diag2 / 5, Up.y +  Diag1 / 3, Text);
	pWind->SetPen(LIMEGREEN, 3);
	pWind->DrawString(Up.x - (Diag2 / 2) - 20, Up.y + (Diag1 / 2), "T");
	pWind->SetPen(INDIANRED, 3);
	pWind->DrawString(Up.x + (Diag2 / 2) + 10, Up.y + (Diag1 / 2), "F");
}

//Draw Connector
//Arrow head
void Output::calcVertexes(Point Start, Point End, double&x1, double&y1, double&x2, double&y2)
{
	double angle = atan2(End.y - Start.y, End.x - Start.x) + cdPi;

	double ArrowLen = 15.0;
	double ArrowAng = 0.7;

	x1 = End.x + ArrowLen * cos(angle - ArrowAng);
	y1 = End.y + ArrowLen * sin(angle - ArrowAng);
	x2 = End.x + ArrowLen * cos(angle + ArrowAng);
	y2 = End.y + ArrowLen * sin(angle + ArrowAng);
}
//Connector with arrow head
void Output::DrawConnector(Point Src, Point Dst, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color

	pWind->DrawLine(Src.x, Src.y, Dst.x, Dst.y);

	double x1, y1, x2, y2;

	calcVertexes(Src, Dst, x1, y1, x2, y2);

	pWind->DrawLine(Dst.x, Dst.y, x1, y1);
	pWind->DrawLine(Dst.x, Dst.y, x2, y2);
}

void Output::DrawBentConnector(Point Src, Point Dst, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color

	pWind->DrawLine(Src.x, Src.y, Dst.x, Src.y);
	Src.x = Dst.x;
	DrawConnector(Src, Dst, Selected);
}

//Prints a message on status bar
void Output::PrintMessage(string msg)
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgClr, 50);
	pWind->SetFont(font, BOLD, BY_NAME, "Lucida Handwriting");
	pWind->DrawString(10, UI.height - UI.StBrWdth / 1.5, msg);
}

//Destructor
Output::~Output()
{
	delete pWind;
}

void Output::setFont(int s)
{
	font = s;
}