#include "ChangeMode.h"
#include "..\ApplicationManager.h"

ChangeMode::ChangeMode(ApplicationManager* pApp) :Action(pApp)
{
}

ChangeMode::~ChangeMode(void)
{
}

void ChangeMode::Execute()
{
	//Get a Pointer to the user Interfaces
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	switch (pIn->GetMode())
	{
	case SIM_MODE:
		pOut->CreateSimulationToolBar();//Create the simulation tool bar 
		pManager->Simulation(); //Run the simulation on the current situation
		pManager->ChangeModeHelper(); //Unselect all the selected components
		//Print Action Message
		pOut->PrintMsg("Simulation Mode Entered!");
		break;

	case DSN_MODE_ADD:
		pOut->CreateDesignADDBar();//Create the add tool bar 

		//Print Action Message
		pOut->PrintMsg("Design Mode Entered!");
		break;


	case DSN_MODE:
		pOut->CreateDesignToolBar();//Create the design tool bar 
		pManager->ChangeModeHelper();//Unselect all the selected components
		//Print Action Message
		pOut->PrintMsg("Returned to Design Mode!");
		break;
	}
}



void ChangeMode::ReadActionParameters()
{}

void ChangeMode::Undo()
{}

void ChangeMode::Redo()
{}

