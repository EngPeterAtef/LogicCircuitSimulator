#ifndef _SAVE_H
#define _SAVE_H

#include "Action.h"


class Save : public Action
{
public:
	Save(ApplicationManager* pApp);
	virtual void Execute();


	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();
};
#endif