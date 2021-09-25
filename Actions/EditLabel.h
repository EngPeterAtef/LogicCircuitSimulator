#ifndef _EDIT_LABEL_H
#define _EDIT_LABEL_H

#include "action.h"

class EditLabel : public Action
{
private:
	int Cx, Cy;
public:
	EditLabel(ApplicationManager* pApp);
	virtual void Execute();

	virtual ~EditLabel(void);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();


	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();
};

#endif