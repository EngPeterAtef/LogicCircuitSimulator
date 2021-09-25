#ifndef _EDIT_CONNECTIONS_H
#define _EDIT_CONNECTIONS_H

#include "action.h"
#include "..\Components\Connection.h"

class EditConnection : public Action
{
private:
	int x1, y1, x2, y2;       //Start and end point of connection
	int inputPinNumber;       //the number (position) of the inputpin of the destination gate
	Component* old_sourceptr; //pointer to the old (already connected) source gate
	Component* old_targetptr; //pointer to the old (already connected) target (destination) gate
	Component* sourceptr; //pointer to the new source gate (that will be connected)
	Component* targetptr; //pointer to the new target (destination) gate (that will be connected)
	Component* con;		  //pointer to the connection that will be edited
	InputPin* TInPin;     //inputpin of the destination gate
	GraphicsInfo Gs;      //coordinates of source gate
	GraphicsInfo Gt;      //coordinates of target gate
	string selection;	  //to select whether the source or destination gate will be edited
public:
	EditConnection(ApplicationManager* pApp);
	virtual void Execute();

	virtual ~EditConnection(void);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();


	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();
};

#endif