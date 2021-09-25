#include "Exit.h"
#include "..\ApplicationManager.h"

Exit::Exit(ApplicationManager* pApp):Action(pApp)
{
}

void Exit::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//ask the user to save the current window
	pOut->PrintMsg("Do you want to save?  <Y/N>");
	string s = pIn->GetSrting(pOut);

	//if yes save it in the savefile
	if (s == "Y"||s == "y")
		pManager->ExecuteAction(SAVE);

	else pOut->ClearStatusBar();
}

void Exit::ReadActionParameters()
{
}

void Exit::Undo()
{
}

void Exit::Redo()
{
}
