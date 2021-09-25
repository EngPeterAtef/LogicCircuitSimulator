#ifndef _CHANGE_MODES_H
#define _CHANGE_MODES_H

#include "action.h"


class ChangeMode : public Action
{
private:

public:

	ChangeMode(ApplicationManager* pApp);
	virtual ~ChangeMode(void);

	//Execute action (code depends on action type)
	virtual void Execute();
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();


	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();
};


#endif