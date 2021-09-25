#ifndef _EXIT_H
#define _EXIT_H

#include "Action.h"


class Exit : public Action
{
public:
	Exit(ApplicationManager* pApp);
	virtual void Execute();

	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();
};
#endif