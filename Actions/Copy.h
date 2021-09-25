#ifndef _COPY_H
#define _COPY_H

#include "action.h"

class Copy : public Action
{
	int Cx, Cy;
public:
	Copy(ApplicationManager* pApp);
	virtual void Execute();

	virtual ~Copy(void);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();


	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();
};

#endif
