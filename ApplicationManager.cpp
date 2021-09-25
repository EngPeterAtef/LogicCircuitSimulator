#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions/AddXNORGate2.h"
#include "Actions/AddXORgate3.h"
#include "Actions\AddXNORgate3.h"
#include "Actions/AddANDgate3.h"
#include "Actions/addORgate2.h"
#include "Actions/addORgate3.h"
#include "Actions/AddNOTgate.h"
#include "Actions/AddNANDgate2.h"
#include "Actions/AddNANDgate3.h"
#include "Actions/AddNORgate2.h"
#include "Actions/AddNORgate3.h"
#include "Actions/AddXORgate2.h"
#include "Actions/ChangeMode.h"
#include "Actions/AddBuffgate.h"
#include"Actions/Select.h"
#include "Actions/EditLabel.h"
#include "Actions/SetLabel.h"
#include "Actions/EditConnection.h"
#include "Actions/Delete.h"
#include "Actions\AddConnection.h"
#include "Actions\AddLED.h"
#include "Actions/Copy.h"
#include "Actions/Paste.h"
#include "Actions/Cut.h"
#include "Actions/Exit.h"
#include "Actions/AddSwitch.h"
#include "Components/Connection.h"
#include"Actions/Save.h"
#include"Actions/Load.h"
#include "Components/Buffer.h"
#include "Components/NOT.h"
#include"Components/NAND2.h"
#include"Components/NAND3.h"
#include"Actions/AddTruthTable.h"

ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	loadHelper = false;
	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
	SelectedCount = 0;
	CCount = 1;
	lastID = 0;
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;		

	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetComponentType() != "Connection" && CompList[i]->getID() == 0)
		{
			CompList[i]->setID(CCount++);
		}
	}
}
////////////////////////////////////////////////////////////////////
ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;

		case ADD_XNOR_GATE_2:
			pAct = new AddXNORGate2(this);
			break;

		case ADD_XOR_GATE_3:
			pAct = new AddXORgate3(this);
			break;

		case ADD_XNOR_GATE_3:
			pAct = new AddXNORgate3(this);
			break;

		case ADD_AND_GATE_3:
			pAct = new AddANDgate3(this);
			break;

		case ADD_OR_GATE_3:
			pAct = new AddORgate3(this);
			break;

		case ADD_OR_GATE_2:
			pAct = new AddORgate2(this);
			break;

		case ADD_INV:
			pAct = new AddNOTgate(this);
			break;

		case ADD_Buff:
			pAct = new AddBuffgate(this);
			break;

		case ADD_NAND_GATE_2:
			pAct = new AddNANDgate2(this);
			break;

		case ADD_NAND_GATE_3:
			pAct = new AddNANDgate3(this);
			break;

		case ADD_NOR_GATE_2:
			pAct = new AddNORgate2(this);
			break;

		case ADD_NOR_GATE_3:
			pAct = new AddNORgate3(this);
			break;

		case ADD_XOR_GATE_2:
			pAct = new AddXORgate2(this);
			break;

		case CHANGE_MODE:
			pAct = new ChangeMode(this);
			break;

		case EDIT_Label:
			pAct = new EditLabel(this);
			break;

		case ADD_Label:
			pAct = new SetLabel(this);
			break;

		case Edit_CONNECTION:
			pAct = new EditConnection(this);
			break;

		case DEL:
			pAct = new Delete(this);
			break;

		case ADD_CONNECTION:
			pAct = new AddConnection(this);
			break;

		case ADD_LED:
			pAct = new AddLED(this);
			break;

		case SELECT:
			pAct = new Select(this);
			break;

		case COPY:
			pAct = new Copy(this);
			break;

		case PASTE:
			pAct = new Paste(this);
			break;
			
		case CUT:
			pAct = new Cut(this);
			break;

		case ADD_Switch:
			pAct = new AddSwitch(this);
			break;

		case SAVE:
			pAct = new Save(this);
			break;

		case LOAD:
			pAct = new Load(this);
			break;

		case Create_TruthTable:
			pAct = new AddTruthTable(this);
			break;

		case EXIT:
			pAct = new Exit(this);
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
///////////////////////////////////////////////////////////////////////////////
void ApplicationManager::UpdateInterface()
{
	OutputInterface->ClearDrawingArea();

	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->Draw(OutputInterface);
		GraphicsInfo g = CompList[i]->getCoordinates();
		int x = g.x1 + 17;
		int y = g.y1 -15;

		OutputInterface->DrawsLabel(x, y, CompList[i]->GetLabel());
	}
}
///////////////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}
///////////////////////////////////////////////////////////////////////////////
string ApplicationManager::getTypeofComponent()
{
	return Type;
}
///////////////////////////////////////////////////////////////////////////////
void ApplicationManager::DeleteHelper(int I)
{
	/*  i is the index of the selected component
		j is the index of the connection that will be deleted
		k is the index of the of the destination gate of the connection in j
		m is the index of the of the source gate of the connection in j
		l is the index of the inputpin of the gate in k
		con_i is used to check whether i is a connection
		con_j is used to check whether j is a connection
		con_k is used to check whether k is a connection
		con_m is used to check whether m is a connection
	*/
	int i = I;
	Connection* con_i = dynamic_cast<Connection*>(CompList[i]); //checks if the selected component is a connection
	if (con_i) //if the selected component is a connection
	{
		for (int k = 0; k < CompCount; k++)//loop on components to find the destination gate of this connection
		{
			Connection* con_k = dynamic_cast<Connection*>(CompList[k]);
			if (!con_k)
			{
				int n = CompList[k]->getInputPinNumber();
				InputPin* I = CompList[k]->getInputPins();
				OutputPin* O = CompList[k]->getOutputPin();
				if (con_i->getSourcePin() == O)
				{
					O->Disconnect(con_i);
				}
				else
				{
					for (int l = 0; l < n; l++)
					{
						if (con_i->getDestPin() == &I[l])
						{
							I[l].setConnected(false);
							switch (l)
							{
							case 0:
								CompList[k]->setInputPinStatus(1, LOW);
								break;
							case 1:
								CompList[k]->setInputPinStatus(2, LOW);
								break;
							case 2:
								CompList[k]->setInputPinStatus(3, LOW);
								break;
							}
						}
					}
				}
			}
		}
	}
	else //if selected component is a gate, we search for all the connections attached to it
		for (int j = 0; j < CompCount; j++)
		{
			Connection* con_j = dynamic_cast<Connection*>(CompList[j]);
			if (con_j)
			{
				if (con_j->getSourcePin() == CompList[i]->getOutputPin())//connections out of the gate
				{

					for (int k = 0; k < CompCount; k++)//loop on components to find the destination gate of this connection
					{
						Connection* con_k = dynamic_cast<Connection*>(CompList[k]);
						if (!con_k)
						{
							int n = CompList[k]->getInputPinNumber();
							InputPin* I = CompList[k]->getInputPins();
							for (int l = 0; l < n; l++)
							{
								if (con_j->getDestPin() == &I[l])
								{
									delete CompList[j];
									CompList[j] = CompList[CompCount - 1];
									CompList[CompCount - 1] = nullptr; //replace the deleted component in j by the last component in complist
									CompCount--;
									j--;                //go back 1 step to check the new component added in j due to the delete
									k = 0;				//reset the counter k to loop on the updated component list
									I[l].setConnected(false);
									switch (l)
									{
									case 0:
										CompList[k]->setInputPinStatus(1, LOW);
										break;
									case 1:
										CompList[k]->setInputPinStatus(2, LOW);
										break;
									case 2:
										CompList[k]->setInputPinStatus(3, LOW);
										break;
									}
								}
							}
						}
					}
				}
				else  //connections entering the selected gate
				{
					int n = CompList[i]->getInputPinNumber();
					InputPin* I = CompList[i]->getInputPins();
					for (int l = 0; l < n; l++)
					{
						if (con_j->getDestPin() == &I[l])
						{
							for (int k = 0; k < CompCount; k++)//loop on components to find the source gate of this connection
							{
								Connection* con_k = dynamic_cast<Connection*>(CompList[k]);
								if (!con_k)
								{
									OutputPin* O = CompList[k]->getOutputPin();
									if (con_j->getSourcePin() == O)
									{
										O->Disconnect(con_j);
									}
								}
							}
							delete CompList[j];
							CompList[j] = CompList[CompCount - 1];
							CompList[CompCount - 1] = nullptr;
							CompCount--;
							j--;
						}
					}

				}

			}
		}

	delete CompList[i];
	CompList[i] = CompList[CompCount - 1];
	CompList[CompCount - 1] = nullptr;

	SelectedCount--;
	CompCount--;
}

void ApplicationManager::DeleteComponents()
{
	if (SelectedCount == 0) 
		OutputInterface->PrintMsg("There is no selected component(s), please select one or more component to delete");
	else
	{
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i]->IsSelected())
			{
				DeleteHelper(i);
				i--;
			}
		}
		OutputInterface->PrintMsg("Component(s) deleted");
	}
}

void ApplicationManager::DeleteComponent(Component* C) {

	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] == C)
		{
			DeleteHelper(i);
			break;
		}
	}

}
///////////////////////////////////////////////////////////////////////////////
void ApplicationManager::SelectComponent(Point ClickedPoint)
{
	
	int x = ClickedPoint.x;
	int y = ClickedPoint.y;
	if (UI.AppMode == DESIGN || UI.AppMode == DESIGN_ADD)
	{
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i]->InRange(x, y))
			{
				bool toBeSelected = CompList[i]->IsSelected();
				CompList[i]->SetSelected(!toBeSelected);
				CompList[i]->Draw(OutputInterface);

				if (toBeSelected)
					SelectedCount--;
				else SelectedCount++;

				OutputInterface->ClearStatusBar();
			}
		}
	}
	else if (UI.AppMode == SIMULATION)
	{
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i]->InRange(x, y))
			{
				bool toBeSelected = CompList[i]->IsSelected();
				CompList[i]->SetSelected(!toBeSelected);
				CompList[i]->Draw(OutputInterface);

				if (toBeSelected)
					SelectedCount--;
				else SelectedCount++;


				if (CompList[i]->GetComponentType() == "Switch")
				{
					if (toBeSelected)
						CompList[i]->setInputPinStatus(0, LOW);
					else
						CompList[i]->setInputPinStatus(0, HIGH);

					Simulation();
				}

				OutputInterface->ClearStatusBar();
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
void ApplicationManager::Simulation()
{
	for (int i = 0; i < CompCount; i++)
	{
		for (int i = 0; i < CompCount; i++)
		{
			CompList[i]->Operate();
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
void ApplicationManager::getSource_Target_and_InputPin(Connection* c, Component*& sourcegate, Component*& targetgate, int& pinposition)
{
	bool flag1 = false, flag2 = false;
	for (int k = 0; k < CompCount; k++)//loop on components to find the destination gate of this connection
	{
		Connection* con_k = dynamic_cast<Connection*>(CompList[k]);
		if (!con_k)
		{
			if (c->getSourcePin() == CompList[k]->getOutputPin())
			{
				sourcegate = CompList[k];
				flag1 = true;
			}
			else
			{
				int n = CompList[k]->getInputPinNumber();
				InputPin* I = CompList[k]->getInputPins();
				for (int l = 0; l < n; l++)
				{
					if (c->getDestPin() == &I[l])
					{
						targetgate = CompList[k];
						pinposition = l;
						flag2 = true;
					}
				}
			}
			if (flag1 && flag2)
				return;
		}
	}
}

void ApplicationManager::saveComponents()
{
	int order;
	Component* Cs, * Ct;
	int NC = 0; //CC is number of connections and NC is the number of non-connection components
	outputFile.open("SaveFile.txt");
	Connection* con;
	for (size_t i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetComponentType() != "Connection")
			NC++;
	}
	outputFile << NC << endl;
	for (size_t i = 0; i < CompCount; i++)
	{
		con = dynamic_cast<Connection*>(CompList[i]);
		if (con == NULL) {
			outputFile << CompList[i]->GetComponentType() << " " << CompList[i]->getID() << " ";

			if (CompList[i]->GetLabel() == " ")
				outputFile << "$" << " ";
			else
				outputFile << CompList[i]->GetLabel() << " ";

			outputFile << CompList[i]->getCoordinates().x1 << " " << CompList[i]->getCoordinates().y1 << endl;

		}
		
	}
	outputFile << "Connections"<< endl;
	
	for (size_t i = 0; i < CompCount; i++)
	{
		con = dynamic_cast<Connection*>(CompList[i]);
		if (con !=NULL)
		{
			getSource_Target_and_InputPin(con, Cs, Ct,order);
			outputFile << Cs->getID() << "\t" << Ct->getID() << "\t" << order+1<<endl;

		}
	}
	outputFile << "-1";
	OutputInterface->PrintMsg("Window is saved successfully.");
	outputFile.close();
}
///////////////////////////////////////////////////////////////////////////////
void ApplicationManager::loadComponents(string line)
{
	if (loadHelper == false)
	{
		for (int i = 0; i < CompCount; i++)
			delete CompList[i];
		CompCount = 0;
		loadHelper = true;
	}

	int index;
	string type;
	int numComp,id1,id2,inputPinNumber;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == ' ')
		{
			index = i;
			break;
		}
		type += line[i];
	}
		
	if (type == "AND2")
	{
		string  ID, label, x, y;

		getLoadData(line, index, ID, label, x, y);//get the data of the AND gate (label, ID, Coordinates)
		GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate
		
		AND2* pA = new AND2(GInfo, AND2_FANOUT);
		AddComponent(pA);
		int c = CompCount - 1;

		if (label == "$")			
			CompList[c]->SetLabel(" ");
		else CompList[c]->SetLabel(label);
		
		
		CompList[c]->setID(stoi(ID));
	}
	else if (type == "AND3")
	{
		string  ID, label, x, y;

		getLoadData(line, index, ID, label, x, y);
		GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

		AND3* pA = new AND3(GInfo, AND2_FANOUT);
		AddComponent(pA);
		int c = CompCount - 1;

		if (label == "$")
			CompList[c]->SetLabel(" ");
		else CompList[c]->SetLabel(label);

		CompList[c]->setID(stoi(ID));
	}
	else if (type == "OR2")
	{
		string  ID, label, x, y;
		
		getLoadData(line, index, ID, label, x, y);
		GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

		OR2* pA = new OR2(GInfo, AND2_FANOUT);
		AddComponent(pA);
		int c = CompCount - 1;

		if (label == "$")
			CompList[c]->SetLabel(" ");
		else CompList[c]->SetLabel(label);

		CompList[c]->setID(stoi(ID));
	}
	else if (type == "OR3")
	{
	string  ID, label, x, y;
	
	getLoadData(line, index, ID, label, x, y);
	GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

	OR3* pA = new OR3(GInfo, AND2_FANOUT);
	AddComponent(pA);
	int c = CompCount - 1;

	if (label == "$")
		CompList[c]->SetLabel(" ");
	else CompList[c]->SetLabel(label);

	CompList[c]->setID(stoi(ID));
	}
	else if (type == "Switch")
	{
		string  ID, label, x, y;

		getLoadData(line, index, ID, label, x, y);
		GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

		Switch* pA = new Switch(GInfo);
		AddComponent(pA);
		int c = CompCount - 1;

		if (label == "$")
			CompList[c]->SetLabel(" ");
		else CompList[c]->SetLabel(label);

		CompList[c]->setID(stoi(ID));
	}
	else if (type == "LED")
	{
		string  ID, label, x, y;

		getLoadData(line, index, ID, label, x, y);

		int id = stoi(ID);
		if (id == -1)
			return;

		GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

		LED* pA = new LED(GInfo);
		AddComponent(pA);
		int c = CompCount - 1;

		if (label == "$")
			CompList[c]->SetLabel("");
		else CompList[c]->SetLabel(label);

		CompList[c]->setID(id);
	}
	else if (type == "Buffer")
	{
	string  ID, label, x, y;

	getLoadData(line, index, ID, label, x, y);
	GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

	Buffer* pA = new Buffer(GInfo, AND2_FANOUT);
	AddComponent(pA);
	int c = CompCount - 1;

	if (label == "$")
		CompList[c]->SetLabel(" ");
	else CompList[c]->SetLabel(label);

	CompList[c]->setID(stoi(ID));
	}
	else if (type == "NOT")
	{
	string  ID, label, x, y;

	getLoadData(line, index, ID, label, x, y);
	GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

	NOT* pA = new NOT(GInfo, AND2_FANOUT);
	AddComponent(pA);
	int c = CompCount - 1;

	if (label == "$")
		CompList[c]->SetLabel(" ");
	else CompList[c]->SetLabel(label);

	CompList[c]->setID(stoi(ID));
	}
	else if (type == "NAND2")
	{
	string  ID, label, x, y;

	getLoadData(line, index, ID, label, x, y);
	GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

	NAND2* pA = new NAND2(GInfo, AND2_FANOUT);
	AddComponent(pA);
	int c = CompCount - 1;

	if (label == "$")
		CompList[c]->SetLabel(" ");
	else CompList[c]->SetLabel(label);

	CompList[c]->setID(stoi(ID));
	}
	else if (type == "NAND3")
	{
	string  ID, label, x, y;

	getLoadData(line, index, ID, label, x, y);
	GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

	NAND3* pA = new NAND3(GInfo, AND2_FANOUT);
	AddComponent(pA);
	int c = CompCount - 1;

	if (label == "$")
		CompList[c]->SetLabel(" ");
	else CompList[c]->SetLabel(label);

	CompList[c]->setID(stoi(ID));
	}
	else if (type == "NOR2")
	{
	string  ID, label, x, y;

	getLoadData(line, index, ID, label, x, y);
	GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

	NOR2* pA = new NOR2(GInfo, AND2_FANOUT);
	AddComponent(pA);
	int c = CompCount - 1;

	if (label == "$")
		CompList[c]->SetLabel(" ");
	else CompList[c]->SetLabel(label);

	CompList[c]->setID(stoi(ID));
	}
	else if (type == "NOR3")
	{
	string  ID, label, x, y;

	getLoadData(line, index, ID, label, x, y);
	GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

	NOR3* pA = new NOR3(GInfo, AND2_FANOUT);
	AddComponent(pA);
	int c = CompCount - 1;

	if (label == "$")
		CompList[c]->SetLabel(" ");
	else CompList[c]->SetLabel(label);

	CompList[c]->setID(stoi(ID));
	}
	else if (type == "XOR2")
	{
	string  ID, label, x, y;

	getLoadData(line, index, ID, label, x, y);
	GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

	XOR2* pA = new XOR2(GInfo, AND2_FANOUT);
	AddComponent(pA);
	int c = CompCount - 1;

	if (label == "$")
		CompList[c]->SetLabel(" ");
	else CompList[c]->SetLabel(label);

	CompList[c]->setID(stoi(ID));
	}
	else if (type == "XOR3")
	{
	string  ID, label, x, y;

	getLoadData(line, index, ID, label, x, y);
	GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

	XOR3* pA = new XOR3(GInfo, AND2_FANOUT);
	AddComponent(pA);
	int c = CompCount - 1;

	if (label == "$")
		CompList[c]->SetLabel(" ");
	else CompList[c]->SetLabel(label);

	CompList[c]->setID(stoi(ID));
	}
	else if (type == "XNOR2")
	{
	string  ID, label, x, y;

	getLoadData(line, index, ID, label, x, y);
	GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

	XNOR2* pA = new XNOR2(GInfo, AND2_FANOUT);
	AddComponent(pA);
	int c = CompCount - 1;

	if (label == "$")
		CompList[c]->SetLabel(" ");
	else CompList[c]->SetLabel(label);

	CompList[c]->setID(stoi(ID));
	}
	else if (type == "XNOR3")
	{
	string  ID, label, x, y;

	getLoadData(line, index, ID, label, x, y);
	GraphicsInfo GInfo = getLoadData(x, y, ID); //Gfx info to be used to construct the AND2 gate

	XNOR3* pA = new XNOR3(GInfo, AND2_FANOUT);
	AddComponent(pA);
	int c = CompCount - 1;

	if (label == "$")
		CompList[c]->SetLabel(" ");
	else CompList[c]->SetLabel(label);

	CompList[c]->setID(stoi(ID));
	}
	else if (type == "Connections")
		return;
	else //for numbers
	{
		int count = 1;
		string n1,n2,n3;
		for (int i = 0; i < line.length(); i++)
		{
			if (count == 1 && line[i] != '\t')
				n1 += line[i];
			else if (count == 2 && line[i] != '\t')
				n2 += line[i];
			else if (count == 3 && line[i] != '\t')
				n3 += line[i];
			if (line[i] == '\t')
				count++;
		}
		id1 = stoi(n1);
		id2 = stoi(n2);
		inputPinNumber = stoi(n3) - 1;
		GraphicsInfo Gs, Gt;
		Component* sourceptr, * targetptr;
		sourceptr = getComponentByID(id1);
		targetptr = getComponentByID(id2);
		Gs = sourceptr->getCoordinates();
		Gt = targetptr->getCoordinates();
		InputPin* TInPin = &targetptr->getInputPins()[inputPinNumber];
		TInPin->setConnected(true);
		int x1, y1, x2, y2;
		int Wdth = UI.AND2_Width;
		int Len = UI.AND2_Height;
		Switch* S = dynamic_cast<Switch*>(sourceptr);
		if (S)
			y1 = Gs.y1 + Len * 2 / 3; //position of output of switch
		else
			y1 = Gs.y1 + Len / 2;     //position of output of any other gate

		x1 = Gs.x1 + Wdth;
		x2 = Gt.x1;
		int n = targetptr->getInputPinNumber();
		switch (n) //to set the position of inputpin in each gate
		{
		case 1:
			y2 = Gt.y1 + Len / 2;
			break;
		case 2:
			y2 = Gt.y1 + Len / 3;
			break;
		case 3:
			y2 = Gt.y1 + Len / 3 - 6;
			break;
		}
		switch (inputPinNumber)
		{
		case 0:
			break;
		case 1:
			y2 += 15;            //15 is the difference between two consecutive input pins
			break;
		case 2:
			y2 += 30;
			break;
		}
		GraphicsInfo GInfo; //Gfx info to be used to construct the connection
		GInfo.x1 = x1;
		GInfo.y1 = y1;      //source gate outputpin coordinates
		GInfo.x2 = x2;
		GInfo.y2 = y2;      //destination gate inputpin coordinates
		OutputPin* SOutPin = sourceptr->getOutputPin();
		Connection* pA = new Connection(GInfo, SOutPin, TInPin);
		SOutPin->ConnectTo(pA);
		AddComponent(pA);
	}
	Simulation();
}

void ApplicationManager::getLoadData(string line, int index,string& ID, string& label, string& x, string& y)
{
	int count = 1;
	for (int i = index + 1; i < line.length(); i++)
	{
		if (count == 1 && line[i] != ' ')
			ID += line[i];
		else if (count == 2 && line[i] != ' ')
			label += line[i];
		else if (count == 3 && line[i] != ' ')
			x += line[i];
		else if (count == 4 && line[i] != ' ')
			y += line[i];
		if (line[i] == ' ')
			count++;
	}
}

GraphicsInfo ApplicationManager::getLoadData(string&x, string&y, string&ID) {
	int x1 = stoi(x);
	int y1 = stoi(y);
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	int Len = UI.AND2_Width;
	int Width = UI.AND2_Height;
	GInfo.x1 = x1;
	GInfo.x2 = x1 + Len;
	GInfo.y1 = y1;
	GInfo.y2 = y1 + Width;
	return GInfo;
}

void ApplicationManager::setLoadHelper(bool l)
{
	loadHelper = l;
}

Component* ApplicationManager::getComponentByID(int id)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->getID() == id)
			return CompList[i];
	}
	return NULL;
}
void ApplicationManager::setLastID(int s)
{
	lastID = s;
}
///////////////////////////////////////////////////////////////////////////////
int ApplicationManager::SearchForLEDs(Component** s)
{
	int count = 0;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetComponentType() == "LED")
		{
			s[count] = CompList[i];
			count++;
		}
	}
	return count;
}

int ApplicationManager::SearchForSwitches(Component** s)
{
	int count = 0;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetComponentType() == "Switch")
		{
			s[count] = CompList[i];
			Switch* swt = static_cast<Switch*> (s[count]);
			swt->setpreviousstatus(swt->GetOutPinStatus());
			count++;
		}
	}
	return count;
}
///////////////////////////////////////////////////////////////////////////////
Component* ApplicationManager::GetComponent(int index)
{
	return CompList[index];
}
Component* ApplicationManager::getSelectedComponent(int x, int y)
{
	for (int i = CompCount - 1; i >= 0; i--)
	{
		if (CompList[i]->InRange(x, y))
		{
			return CompList[i];
		}
	}
	return NULL;
}
int ApplicationManager::GetComponentCount()
{
	return CompCount;
}

bool ApplicationManager::ComponentHere(int x, int y)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->InRange2(x, y))
		{
			return true;
		}
	}
	return false;
}

void ApplicationManager::ChangeModeHelper()
{
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->SetSelected(false);
		if (CompList[i]->GetComponentType() == "Switch")
			CompList[i]->setInputPinStatus(0, LOW);
	}
}

void ApplicationManager::setTemp(Component* c)
{
	Type = c->GetComponentType();
	tempname = c->GetLabel();
}

string ApplicationManager::getTemp()
{
	return tempname;
}
////////////////////////////////////////////////////////////////////
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
}