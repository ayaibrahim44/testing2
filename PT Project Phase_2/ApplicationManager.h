#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include<vector>

#include "DEFS.h"

#include "Statements\Statement.h"
class Input;
class Output;
#include<fstream>

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart

private:
	int StatCount;		//Actual number of statements
	int ConnCount;		//Actual number of connectors
	Statement* StatList[MaxCount];	//List of all statements (Array of pointers)
	Connector* ConnList[MaxCount];	//List of all connectors (Array of pointers)
	vector<pair<string, double>> Variables;
	vector<string> codeVariables;
	Connector* SelectedCo;		//a pointer to the last selected connector
	Statement *pSelectedStat; //a pointer to the last selected statement
	Statement*pCopiedStatement;
	Statement*pCutStatement;
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

	ifstream Infile;
	ofstream Outfile;

	bool ZoomedIn, ZoomedOut;
	Statement* selectedarray[MaxCount];
	int selectCount;
	Connector* selectedConnectors[MaxCount];	//array of selected connectors
	int CselectCount;		//no. of selected connectors in the array

	Connector**Connect;

public:	
	bool iscopy;
	bool iscut;
	string Lastmsg;
	ApplicationManager(); 
	~ApplicationManager();
	
	bool CheckArea(Point p) const;

	// -- Actions Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Statements/Connector Management Functions
	void AddStatement(Statement* pStat); //Adds a new Statement to the Flowchart
	Statement *GetStatement(Point P) const;	//search for a statement where point P belongs


	void DeleteStatement(Statement*DStat);
	void DeleteConnector(Connector*Con);

	void appAddConnector(Connector* pConn); //Adds a new Connector to the Flowchart
	Connector *GetConnector(Point P) const;	//search for a Connector where point P belongs
	void SetSelectedConnector(Connector*);	//set the connector selected by the user
	Connector* getSelectedConnector() const; 
	Connector** getSelectedConnArray();	//return array of selected connectors
	int getCSelectCount();	//return number of selected connectors
	Statement *	GetCopiedStatement() const;
	Statement*GetCutStatement() const;
	void SetCopiedStatement(Statement*pStat);
	void SetCutStatement(Statement*pStat);
	Statement *GetSelectedStatement() const;	//Returns the selected Statement
	void SetSelectedStatement(Statement *pStat); //Set the Statement selected by the user
	void Managerpaste(Statement*pstat);
	void cutManager(Statement*);
	bool Validate();

	Statement**getSelectArray();
	void unselect(Statement *pStat);
	void unselectCon (Connector*);

	int GetSelectCount();

	Statement* GetStartStat();
	vector<pair<string, double>>& getVariables();

	void setCodeVar();
	vector<string>& getCodeVar();

	void Save();
	void Load();

	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window
	StatementType getStatementType(string);

	int getStatCount() const;
	void setStatCount(int);

	Statement* GetStatement(int id) const; //get a statement using its id

	void ZoomIn();
	void ZoomOut();
	
};

#endif