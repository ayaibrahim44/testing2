#ifndef DEFS_H
#define DEFS_H

//This file contais some global constants and definitions to be used in the project.

enum ActionType //The actions supported (you can add more if needed)
{
	ADD_SMPL_ASSIGN,//Add simple assignment statement
	ADD_VAR_ASSIGN,	//Add variable assignment statement
	ADD_SNGL_OPERAT,
	ADD_IF_CONDITION, //Add a conditional statement (for if and while-loop statements)
	ADD_WHILE_LOOP,

	ADD_CONNECTOR, //Add a connector between two statements
	ADD_READ,
	ADD_WRITE,
	ADD_START,
	ADD_END,
	EDIT_STAT,	//Edit a statement
	
	SELECT,		//Select a statement, a connector

	DEL,		//Delete a figure(s)
	MOVE,		//Move a figure(s)
	RESIZE,		//Resize a figure(s)
	ZOOM_IN,	//zoom in a figure(s)
	ZOOM_OUT,	//zoom out a figure(s)
	COPY,		//copy a statement
	CUT,		//cut a statement
	PASTE,		//paste a statement
	REDO,		//redo action
	UNDO,		//undo last action
	MULT_SELECT,//multiple selection
	COMMENT,	//add a comment

	RUN,		//run code
	CODE,		//convert to c++ code
	STEP,		
	VALIDATE,

	DRAW_AREA,	//a click on drawing area

	SAVE,		//Save the whole graph to a file
	LOAD,		//Load a graph from a file
	EXIT,		//Exit the application
	STATUS,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar
	DSN_MODE,	//Switch to Design mode
	SIM_MODE	//Switch to simulatiom mode
};

enum StatementType
{
	START,
	END,
	READ,
	WRITE,
	SMPLE_ASSIGNMENT,
	VAR_ASSIGNMENT,
	SNGLOPERATOR,
	SMPLE_IFCONDITIONAL,
	VAR_IFCONDITIONAL,
	SMPLE_WHILELOOP,
	VAR_WHILELOOP,
	NO_STAT
};

enum relationalOperators
{
	IsEqual,
	NotEqual,
	Lessthan,
	LessthanOrEqual,
	Greaterthan,
	GreaterthanOrEqual,
	NoOperation
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

#ifndef NULL
#define NULL 0
#endif

#endif