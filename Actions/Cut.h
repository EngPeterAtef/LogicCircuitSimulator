#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include "../Components/Component.h"

class Cut :public Action
{
	int Cx, Cy;
public:
	Cut(ApplicationManager* pApp);
	void Execute();

	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();
	virtual ~Cut();
};

