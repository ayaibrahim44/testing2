#include"AddComment.h"

#include"..\Statements\Statement.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

Comment::Comment(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void Comment::ReadActionParameters()
{

	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	SelStat = pManager->GetSelectedStatement();
	if (SelStat != NULL)
	{
		pOut->PrintMessage("enter your comment");

		comment = pIn->GetString(pOut);
		pOut->ClearStatusBar();
	}
	else
		pOut->PrintMessage("select statement then comment");

}

void Comment::Execute()
{
	ReadActionParameters();
	if (SelStat != NULL)
	{
		SelStat->setComment(comment);
		pManager->Lastmsg = "Comment added";
	}
	else
		pManager->Lastmsg = "select statement then comment";
}