#include "Save.h"
#include "..\ApplicationManager.h"


Save::Save(ApplicationManager* pApp) :Action(pApp)
{

}

void Save::Execute()
{
	//call the save function
	pManager->saveComponents();	
}


void Save::ReadActionParameters()
{
}

void Save::Undo()
{
}

void Save::Redo()
{
}
