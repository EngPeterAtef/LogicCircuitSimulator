#pragma once
#include "AddConnection.h"
#include "..\ApplicationManager.h"
#include"..\Components\Gate.h"
#include"..\Components\LED.h"
#include"..\Components\Switch.h"
#include "..\Components\Connection.h"
#include<iostream>
using namespace std;
AddConnection::AddConnection(ApplicationManager* pApp) :Action(pApp)
{
	sourceptr = NULL;
	targetptr = NULL;
}

AddConnection::~AddConnection(void)
{
}


void AddConnection::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int X, Y;
	//Print Action Message
	pOut->PrintMsg("Adding connection, click on the source gate");

	//Wait for User Input
	pIn->GetPointClicked(X, Y);
	sourceptr = pManager->getSelectedComponent(X, Y);
	LED * L= dynamic_cast<LED*>(sourceptr);
	Connection* C = dynamic_cast<Connection*>(sourceptr);
	if (sourceptr == NULL || L !=NULL || C != NULL || sourceptr->getOutputPin()->getm_conn() >= AND2_FANOUT)
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


	pOut->ClearStatusBar();
	pOut->PrintMsg("Click on the destination gate");

	pIn->GetPointClicked(X, Y);

	targetptr = pManager->getSelectedComponent(X, Y);
	Switch * s= dynamic_cast<Switch*>(targetptr);
	C = dynamic_cast<Connection*>(targetptr);
	if(targetptr == NULL || targetptr == sourceptr || s !=NULL || C != NULL)
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
			pOut->ClearStatusBar();
			pOut->PrintMsg("Connected successfully");
			return;
		}
	}

	inputPinNumber = -1;
	pOut->ClearStatusBar();
	pOut->PrintMsg("All the pins of this gate are connected");
}

void AddConnection::Execute()
{
	
	ReadActionParameters();
	if (inputPinNumber == -1)
		return;

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
		y2 += 15;			//15 is the difference between two consecutive input pins
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
	pManager->AddComponent(pA);

}

void AddConnection::Undo()
{}

void AddConnection::Redo()
{}

