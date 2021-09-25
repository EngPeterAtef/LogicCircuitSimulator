#include "AddXNORGate2.h"
#include "..\ApplicationManager.h"

AddXNORGate2::AddXNORGate2(ApplicationManager* pApp) :Action(pApp)
{
}

AddXNORGate2::~AddXNORGate2(void)
{
}

void AddXNORGate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input XNOR Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddXNORGate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	if (pManager->ComponentHere(Cx, Cy))
	{
		pOut->PrintMsg("Cannot add a component here");
		return;
	}
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	XNOR2* pA = new XNOR2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddXNORGate2::Undo()
{}

void AddXNORGate2::Redo()
{}

