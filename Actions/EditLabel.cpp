#include "EditLabel.h"
#include "..\ApplicationManager.h"


EditLabel::EditLabel(ApplicationManager* pApp) : Action(pApp)
{
}

void EditLabel::Execute()
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


	pOut->PrintMsg("Edit Label: Please, Type in a new label for the selected component !!");


	//Get user input, showing it in the status bar
	string label = pIn->GetSrting(pOut,C->GetLabel());

	//Set the new label to the selected component
	C->SetLabel(label);

	pOut->ClearStatusBar();

}

void EditLabel::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMsg("Click on the component to edit label");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
}


EditLabel::~EditLabel(void)
{
}

void EditLabel::Undo()
{
}

void EditLabel::Redo()
{
}
