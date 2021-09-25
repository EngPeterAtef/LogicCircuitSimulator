#ifndef _DELETE_H
#define _DELETE_H

#include "Action.h"


class Delete : public Action
{
public:
	Delete(ApplicationManager* pApp);
	virtual void Execute();


	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();
};
#endif