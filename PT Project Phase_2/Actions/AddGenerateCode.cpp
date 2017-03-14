

#include "AddGenerateCode.h"
#include "..\Statements\Condition.h"
#include "../Statements/SmpleWhileLoop.h"
#include "../Statements/VarWhileLoop.h"
#include "..\Statements\VarIfCondition.h"
#include "../Statements/SmpleIfCondition.h"
#include "../ApplicationManager.h"

class SmpleIfCondition;

AddGenerateCode::AddGenerateCode(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddGenerateCode::ReadActionParameters()
{
	string file;
	pManager->GetOutput()->PrintMessage("Generate code as..");
	file = pManager->GetInput()->GetString(pManager->GetOutput());
	pManager->GetOutput()->PrintMessage("Generating code..");
	file += ".cpp";
	CppCode.open(file);
}

void AddGenerateCode::Execute()
{
	if (!pManager->Validate()) return;
	ReadActionParameters();
	Statement* Current = pManager->GetStartStat();
	Current->GenerateCode(CppCode);
	pManager->setCodeVar();
	if (pManager->getCodeVar().size() != 0)
	{
		for (int i = 0; i < pManager->getCodeVar().size() - 1; i++)
		{
			CppCode << "double " << pManager->getCodeVar().at(i) << " , ";
		}
		CppCode << "double " << pManager->getCodeVar().at(pManager->getCodeVar().size() - 1) << ";\n";
	}
	Current = Current->getConnector()->getDstStat();
	while (Current->getType() != "END")
	{
		if (dynamic_cast<Condition*>(Current) != NULL)dynamic_cast<Condition*>(Current)->setBlock(NULL);
		Current = Current->GenerateCode(CppCode);
	}
	Current->GenerateCode(CppCode);
	pManager->GetOutput()->PrintMessage("Code generated");
	pManager->Lastmsg = "Code generated";
	CppCode.close();
}
