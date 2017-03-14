
#ifndef ADD_CONNECTOR_H
#define ADD_CONNECTOR_H

#include"Action.h"

class AddConnector : public Action
{
private:
	Point Source;	//Position where the user clicks to add the connector
	Point Destin;
public:
	AddConnector(ApplicationManager *pAppManager);

	//Read Connectors position
	virtual void ReadActionParameters();

	//Create a connector 
	virtual void Execute();

};

#endif