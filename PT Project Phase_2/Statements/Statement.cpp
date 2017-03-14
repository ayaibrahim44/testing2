#include "Statement.h"

int Statement::idSet = 0;

Statement::Statement()	
{ 
	Text = "";
	toCon = 0;
	Comment = { 34, 34 };
	Selected = false;	
	font = 25;
	ID = 0;
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

Point Statement::getPosition() const
{	return Position; }
void Statement::setposition(Point P)
{
	Position = P;

}

void Statement::setID(int i) 
{	ID = i; }

int Statement::getID()
{	return ID; }

string Statement::getType() const
{	return Type; }

Connector** Statement::GetConnectorArray()
{
	return toConnect;
}
int Statement::GetToCon()
{
	return toCon;
}
void Statement::setComment(string T)
{
	Comment = T;
}
string Statement::PrintInfo()
{
	string msg = "Statement: " + Text + "........." "Comment: " + Comment;
	return msg;
}

Statement::~Statement() //to be implemented
{}

int Statement::getIdset()
{
	idSet++;
	return idSet;
}