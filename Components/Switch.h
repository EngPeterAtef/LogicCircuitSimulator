#ifndef _SWITCH_H
#define _SWITCH_H

/*
  Class Switch
  -----------
  - Each switch has no inputs pins and one output pin
*/

#include "Component.h"

class Switch :public Component
{
protected:

	bool closed;
	STATUS previous;
	OutputPin m_OutputPin;	//The Gate output pin
	//think if we want to let more than output
public:
	Switch(const GraphicsInfo& r_GfxInfo);
	virtual void Operate();
	virtual void Draw(Output* pOut);

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n = 0);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual OutputPin* getOutputPin();
	virtual InputPin* getInputPins();
	virtual int getInputPinNumber();
	void setpreviousstatus(int);
	STATUS getpreviousstatus();
	virtual string GetComponentType();


};
#endif