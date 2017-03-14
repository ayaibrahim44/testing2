#ifndef STATEMENT_H
#define STATEMENT_H

#include<vector>
#include<fstream>
using namespace std;

#include "..\defs.h"
#include "Connector.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"

class Connector;
class Output;

//Base class for all Statements
class Statement
{
protected:
	static int idSet;
	Point Position; //position of the statement
	Connector* toConnect[10];		//Connectors going to the statement
	int toCon;
	int ID;			//Each Statement has an ID
	string Type;    //statemet type e.g,: SMPLASSIGN,START,..
	string Text;	//Statement text (e.g.  "X = 5" OR "if(salary > 3000)" and so on )
	string Comment; //comment on the statement 
	bool Selected;	//true if the statement is selected on the folwchart
	int font; //for zoom in/out
	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited

	static int start_count;
	static int end_count;

public:
	void SetStartCount(int x){ start_count = x; }
	int GetStartCount(){ return start_count; }
	void SetEndCount(int x){ end_count = x; }
	int GetEndCount() { return end_count; }

	virtual string getLHS(){ return ""; }
	Statement();
	void SetSelected(bool s);
	bool IsSelected() const;

	void setID(int);
	int getID();
	void setposition(Point P);
	Point getPosition() const;
	string getType() const;

	int getIdset();

										/* Virtual Functions */


	virtual void Draw(Output* pOut) const  = 0 ; //Draw the statement

	virtual Point getInlet() const = 0;
	virtual Point getOutlet() const = 0;

										/* Select functions */

	virtual bool InArea(Point) const = 0;

										/* Determine True/False branch */ //for conditional statements

	virtual bool InFirstHalf(Point) const { return true; } //to determine which outlet in the conditional statement
	virtual void setBranch(bool) {} //to determine the flow of chart //know which branch we deal with
	virtual int getBranch(){ return 0; }

	virtual bool Valid(Output*) {return true;}
										/* Connector setters and getters */ //connect

	virtual void setConnector(Connector*) = 0;
	virtual void setToConnector(Connector*) = 0;
	virtual Connector* getConnector() = 0;
	virtual Connector**GetConnectorArray();
	virtual int GetToCon();
	virtual void deleteCon(Connector*) = 0;

	virtual Connector*getTBranch(){ return 0; }
	virtual Connector*getFBranch(){ return 0; }
										/* Actions applied on the statements*/

	virtual void Edit(Output*pOut,Input*pIn) = 0;
	virtual void setComment(string);

	virtual Statement* Copy() = 0;
	virtual Statement* Cut() = 0;
	virtual Statement* Paste() = 0;

	virtual void Move(Point &P) = 0;

	virtual void Save(ofstream &OutFile) = 0; 	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file

	virtual void ZoomIn(Output* & pOut) = 0;
	virtual void ZoomOut(Output* & pOut) = 0;

	virtual string PrintInfo();

										/* Simulation Mode */

	virtual Statement* GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file
	virtual void Simulate(vector<pair<string, double>>&, Input*, Output*) = 0;	//Execute the statement in the simulation mode
	virtual void watch(vector<pair<string, double>>& variables, Output* pout) = 0;

	virtual ~Statement();
};

#endif