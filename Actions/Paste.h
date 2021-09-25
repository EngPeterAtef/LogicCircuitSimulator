#ifndef _PASTE_H
#define _PASTE_H

#include "action.h"
#include "..\Components\Component.h"

class Paste : public Action
{
private:
	Component* comptemp;
public:
	Paste(ApplicationManager* pApp);
	virtual void Execute();

	virtual ~Paste(void);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();


	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();
};

#endif
