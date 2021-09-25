#include "AddBuffgate.h"
#include "../Components/Buffer.h"
#include "..\ApplicationManager.h"

AddBuffgate::AddBuffgate(ApplicationManager* pApp) :Action(pApp)
{
}

AddBuffgate::~AddBuffgate(void)
{
}

void AddBuffgate::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Buffer Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddBuffgate::Execute()
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

	GraphicsInfo GInfo; //Gfx info to be used to construct the NOT gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	Buffer* PN = new Buffer(GInfo, AND2_FANOUT);
	pManager->AddComponent(PN);
}

void AddBuffgate::Undo()
{}

void AddBuffgate::Redo()
{}
