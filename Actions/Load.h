#ifndef _LOAD_H
#define _LOAD_H

#include "Action.h"


class Load : public Action
{
public:
	Load(ApplicationManager* pApp);
	virtual void Execute();


	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();
};
#endif