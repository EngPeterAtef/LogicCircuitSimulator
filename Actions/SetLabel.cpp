#include "SetLabel.h"
#include "..\ApplicationManager.h"


SetLabel::SetLabel(ApplicationManager* pApp) : Action(pApp)
{
}

void SetLabel::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();

	//get the selected component 
	Component* C = pManager->getSelectedComponent(Cx, Cy);

	//Checks if a component is selected
	if (C == NULL)
	{
		pOut->PrintMsg("There is no component here !!");
		return;
	}


	pOut->PrintMsg("Set Label: Please, Type in a new label for the selected component !!");


	//Get user input, showing it in the status bar
	string label = pIn->GetSrting(pOut);

	//Set the new label to the selected component
	C->SetLabel(label);

	pOut->ClearStatusBar();

}

SetLabel::~SetLabel(void)
{
}

void SetLabel::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMsg("Click on the component to set label");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void SetLabel::Undo()
{
}

void SetLabel::Redo()
{
}
