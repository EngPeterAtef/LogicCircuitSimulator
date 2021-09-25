#pragma once
#ifndef _LED_H
#define _LED_H

#include "Component.h"
class LED : public Component
{

	InputPin m_InputPins;	//inputpin of the LED
	bool light;

public:
	LED(const GraphicsInfo& r_GfxInfo);
	virtual void Operate();
	virtual void Draw(Output* pOut);

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n = 0);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual OutputPin* getOutputPin();
	virtual InputPin* getInputPins();
	virtual int getInputPinNumber();

	virtual string GetComponentType();


};
#endif

