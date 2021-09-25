#include "EditConnection.h"
#include "..\ApplicationManager.h"
#include"..\Components\Gate.h"
#include"..\Components\LED.h"
#include"..\Components\Switch.h"
#include<iostream>
EditConnection::EditConnection(ApplicationManager* pApp):Action(pApp)
{
	old_sourceptr = NULL;
	old_targetptr = NULL;
	sourceptr = NULL;
	targetptr = NULL;
	con = NULL;
}

void EditConnection::Execute()
{
	ReadActionParameters();
	if (inputPinNumber == -1)
		return;

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int Wdth = UI.AND2_Width;
	int Len = UI.AND2_Height;
	GraphicsInfo GInfo; //Gfx info to be used to construct the connection
	OutputPin* SOutPin; 
	Switch* S;
	int n;
	string label = con->GetLabel();
	pManager->DeleteComponent(con);
	if (selection == "s" || selection == "S")
	{
		SOutPin = sourceptr->getOutputPin();
		TInPin->setConnected(true);
		n = old_targetptr->getInputPinNumber();
		S = dynamic_cast<Switch*>(sourceptr);
	}
	else if (selection == "d" || selection == "D")
	{
		SOutPin = old_sourceptr->getOutputPin();
		n = targetptr->getInputPinNumber();
		S = dynamic_cast<Switch*>(old_sourceptr);
	}

	if (S)
		y1 = Gs.y1 + Len * 2 / 3; //position of output of switch
	else
		y1 = Gs.y1 + Len / 2;     //position of output of any other gate

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
	x1 = Gs.x1 + Wdth;
	x2 = Gt.x1;

	switch (inputPinNumber)
	{
	case 0:
		break;
	case 1:
		y2 += 15;			//15 is the difference between two consecutive input pins
		break;
	case 2:
		y2 += 30;
		break;
	}
	GInfo.x1 = x1;
	GInfo.y1 = y1;      //source gate outputpin coordinates
	GInfo.x2 = x2;
	GInfo.y2 = y2;      //destination gate inputpin coordinates
	
	Connection* pA = new Connection(GInfo, SOutPin, TInPin);
	SOutPin->ConnectTo(pA);
	pManager->AddComponent(pA);
	pA->SetLabel(label);

	pOut->ClearStatusBar();
}

void EditConnection::ReadActionParameters()
{
	int x, y;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Click on the connection to edit it");

	pIn->GetPointClicked(x, y);
	con = pManager->getSelectedComponent(x, y);
	Connection* C = dynamic_cast<Connection*>(con);
	if (C)
	{
		pManager->getSource_Target_and_InputPin(C, old_sourceptr, old_targetptr, inputPinNumber);

		pOut->ClearStatusBar();
		pOut->PrintMsg("Do you want to change its source or destination?   <S/D>");
		selection = pIn->GetSrting(pOut);
		if (selection == "s"|| selection == "S")
		{
			pOut->PrintMsg("Click on the new source gate");
			pIn->GetPointClicked(x, y);
			sourceptr = pManager->getSelectedComponent(x, y);
			LED* L = dynamic_cast<LED*>(sourceptr);
			Connection* C2 = dynamic_cast<Connection*>(sourceptr);
			if (sourceptr == NULL || L != NULL || C2 != NULL || sourceptr->getOutputPin()->getm_conn() >= AND2_FANOUT)
			{
				if (sourceptr == NULL)
				{
					pOut->ClearStatusBar();
					pOut->PrintMsg("No gate is selected");
				}
				else if (L != NULL)
				{
					pOut->ClearStatusBar();
					pOut->PrintMsg("LED can't be used as an input to the connection");
				}
				else if (sourceptr->getOutputPin()->getm_conn() >= AND2_FANOUT)
				{
					pOut->ClearStatusBar();
					pOut->PrintMsg("Maximum fan out, can't connect more connections");
				}
				inputPinNumber = -1;
				return;
			}
			Gs = sourceptr->getCoordinates();
			Gt = old_targetptr->getCoordinates();
			TInPin = &old_targetptr->getInputPins()[inputPinNumber];
		}
		else if (selection == "d" || selection == "D")
		{
			pOut->PrintMsg("Click on the new destination gate");
			pIn->GetPointClicked(x, y);
			targetptr = pManager->getSelectedComponent(x, y);
			Switch* s = dynamic_cast<Switch*>(targetptr);
			Connection* C2 = dynamic_cast<Connection*>(targetptr);
			if (targetptr == NULL || targetptr == sourceptr || s != NULL || C2 != NULL )
			{
				if (targetptr == NULL)
				{
					pOut->ClearStatusBar();
					pOut->PrintMsg("No gate is selected");
				}
				else if (targetptr == sourceptr)
				{
					pOut->ClearStatusBar();
					pOut->PrintMsg("Can't connect to the same gate");
				}
				else if (s != NULL)
				{
					pOut->ClearStatusBar();
					pOut->PrintMsg("Switch can't be used as an output to the connection");
				}

				inputPinNumber = -1;
				return;

			}
			InputPin* TInPinS = targetptr->getInputPins();
			int i;
			int n = targetptr->getInputPinNumber();
			for (i = 0; i < n; i++)
			{
				if (TInPinS[i].getConnected() == false)
				{
					inputPinNumber = i;
					TInPinS[i].setConnected(true);
					TInPin = &TInPinS[i];
					Gt = targetptr->getCoordinates();
					Gs = old_sourceptr->getCoordinates();
					pOut->ClearStatusBar();
					return;
				}
			}
			inputPinNumber = -1;
			pOut->ClearStatusBar();
			pOut->PrintMsg("All the pins of this gate are connected");
			return;
		}

	}
	else
	{
		pOut->PrintMsg("No connection is clicked");
		inputPinNumber = -1;
	}
}

EditConnection::~EditConnection(void)
{
}


void EditConnection::Undo()
{
}

void EditConnection::Redo()
{
}
