#ifndef _SET_LABEL_H
#define _SET_LABEL_H

#include "action.h"

class SetLabel : public Action
{
private:
	int Cx, Cy;
public:
	SetLabel(ApplicationManager* pApp);
	virtual void Execute();

	virtual ~SetLabel(void);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();


	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();
};

#endif