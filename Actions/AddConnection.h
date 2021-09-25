#ifndef _ADD_CONNECTION_H
#define _ADD_CONNECTION_H

#include "action.h"
#include "..\Components\Connection.h"

class AddConnection : public Action
{
private:
	int x1, y1, x2, y2;   //Start and end point of connection
	int inputPinNumber;   //the number (position) of the inputpin that will be connected
	GraphicsInfo Gs;      //coordinates of source gate
	GraphicsInfo Gt;      //coordinates of target gate
	Component* sourceptr; //pointer to the source gate
	Component* targetptr; //pointer to the target (destination) gate
	InputPin* TInPin;     //inputpin of the destination gate
public:
	AddConnection(ApplicationManager* pApp);
	virtual ~AddConnection(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif

