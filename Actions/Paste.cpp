#include "Paste.h"
#include "..\ApplicationManager.h"

Paste::Paste(ApplicationManager* pApp):Action(pApp)
{
}

void Paste::Execute()
{
	//get the label of the temporary component 
	string name = pManager->getTemp();

	//get the type of the temporary component
	string type = pManager->getTypeofComponent();

	if (type == "AND2")
		pManager->ExecuteAction(ADD_AND_GATE_2);
	else if (type == "AND3")
		pManager->ExecuteAction(ADD_AND_GATE_3);
	else if (type == "Buffer")
		pManager->ExecuteAction(ADD_Buff);
	else if (type == "LED")
		pManager->ExecuteAction(ADD_LED);
	else if (type == "NAND2")
		pManager->ExecuteAction(ADD_NAND_GATE_2);
	else if (type == "NAND3")
		pManager->ExecuteAction(ADD_NAND_GATE_3);
	else if (type == "NOR2")
		pManager->ExecuteAction(ADD_NOR_GATE_2);
	else if (type == "NOR3")
		pManager->ExecuteAction(ADD_NAND_GATE_3);
	else if (type == "NOT")
		pManager->ExecuteAction(ADD_INV);
	else if (type == "OR2")
		pManager->ExecuteAction(ADD_OR_GATE_2);
	else if (type == "OR3")
		pManager->ExecuteAction(ADD_OR_GATE_3);
	else if (type == "Switch")
		pManager->ExecuteAction(ADD_Switch);
	else if (type == "XNOR2")
		pManager->ExecuteAction(ADD_XNOR_GATE_2);
	else if (type == "XNOR3")
		pManager->ExecuteAction(ADD_XNOR_GATE_3);
	else if (type == "XOR2")
		pManager->ExecuteAction(ADD_XOR_GATE_2);
	else if (type == "XOR3")
		pManager->ExecuteAction(ADD_XOR_GATE_3);

	int count = pManager->GetComponentCount();
	comptemp = pManager->GetComponent(count - 1);

	//but the previous label in the new component
	comptemp->SetLabel(name);

}

Paste::~Paste(void)
{
}

void Paste::ReadActionParameters()
{
}

void Paste::Undo()
{
}

void Paste::Redo()
{
}
