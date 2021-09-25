#ifndef _SELECT_H
#define _SELECT_H

#include "action.h"

class Select : public Action
{
	bool selected;
public:
	Select(ApplicationManager* pApp);
	virtual void Execute();

	virtual ~Select(void);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters() ;
	

	//To undo this action (code depends on action type)
	virtual void Undo() ;

	//To redo this action (code depends on action type)
	virtual void Redo() ;
};

#endif