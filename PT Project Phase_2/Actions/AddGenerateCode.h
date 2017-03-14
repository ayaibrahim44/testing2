
#ifndef ADD_GENERATE_CODE_H
#define ADD_GENERATE_CODE_H
using namespace std;
#include<fstream>
#include"Action.h"

class AddGenerateCode : public Action
{
	ofstream CppCode;
public:
	AddGenerateCode(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif