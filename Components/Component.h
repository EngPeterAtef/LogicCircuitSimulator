#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"
#include "OutputPin.h"
#include "InputPin.h"


//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
protected:
	int ID;
	bool select;
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
public:
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself


	virtual bool InRange(int x, int y);
	virtual bool InRange2(int x, int y);


	bool IsSelected();
	void SetSelected(bool selected);


	string GetLabel();
	void SetLabel(string label);
	GraphicsInfo getCoordinates();

	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.

	virtual OutputPin* getOutputPin() = 0;
	virtual InputPin* getInputPins() = 0; //to be used in addconnection
	virtual int getInputPinNumber() = 0;

	void setID(int x);
	int getID() const;
	
	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
	virtual string GetComponentType() = 0;

};

#endif

