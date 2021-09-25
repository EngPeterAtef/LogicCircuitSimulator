#include "Delete.h"
#include "..\ApplicationManager.h"


Delete::Delete(ApplicationManager* pApp) :Action(pApp)
{

}

void Delete::Execute()
{
	//call the delete function 
	pManager->DeleteComponents();
	
}


void Delete::ReadActionParameters()
{
}

void Delete::Undo()
{
}

void Delete::Redo()
{
}
