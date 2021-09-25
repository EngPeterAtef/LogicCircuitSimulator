#include "Copy.h"
#include "..\ApplicationManager.h"

Copy::Copy(ApplicationManager* pApp) : Action(pApp)
{

}

void Copy::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	//get the selected gate
	Component* C = pManager->getSelectedComponent(Cx, Cy);

	//check if there is no gate selected
	if (C == NULL)
	{
		pOut->PrintMsg("There is no component here !!");
		return;
	}

	pManager->setTemp(C);
	pOut->PrintMsg("The component has been copied");
}

Copy::~Copy(void)
{
}

void Copy::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click on the component to be Copied");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);
	
	//Clear Status Bar
	pOut->ClearStatusBar();
}

void Copy::Undo()
{
}

void Copy::Redo()
{
}
