#include "Cut.h"

Cut::Cut(ApplicationManager* pApp) : Action(pApp)
{

}

void Cut::Execute()
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

	C->SetSelected(true);
	pManager->DeleteComponent(C);
	
	pOut->PrintMsg("The component has been cutted");
}

void Cut::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Print Action Message
	pOut->PrintMsg("Click on a Component to be cut");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void Cut::Undo()
{
}

void Cut::Redo()
{
}

Cut::~Cut()
{
}
