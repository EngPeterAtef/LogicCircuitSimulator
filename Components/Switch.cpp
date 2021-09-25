#include "Switch.h"

Switch::Switch(const GraphicsInfo& r_GfxInfo):m_OutputPin(1)
{
    m_GfxInfo.x1 = r_GfxInfo.x1;
    m_GfxInfo.y1 = r_GfxInfo.y1;
    m_GfxInfo.x2 = r_GfxInfo.x2;
    m_GfxInfo.y2 = r_GfxInfo.y2;
    closed = false;
	ID = 0;
}

void Switch::Operate()
{
	//caclulate the output status of the switch
	if (closed)
		this->m_OutputPin.setStatus(HIGH);
	
	else
		this->m_OutputPin.setStatus(LOW);
}

void Switch::Draw(Output * pOut)
{
	//Call output class and pass led drawing info to it.
	if (m_GfxInfo.y1 > UI.ToolBarHeight && m_GfxInfo.y2 < UI.height - UI.StatusBarHeight)
	{
		pOut->DrawSWITCH(m_GfxInfo, select, closed);
	}
}


//returns status of outputpin
int Switch::GetOutPinStatus()
{
	return closed;
}

void Switch::setpreviousstatus(int s)
{
	if (s == 1)
		previous = HIGH;
	else previous = LOW;

}

STATUS Switch::getpreviousstatus()
{
	return previous;
}

//returns status of Inputpin #n
int Switch::GetInputPinStatus(int n)
{
	return -1;
}

//Set status of an input pin ot HIGH or LOW


//Set status of an input pin ot HIGH or LOW
void Switch::setInputPinStatus(int n, STATUS s)
{
	if (s == LOW)
		this->closed = false;

	if (s == HIGH)
		this->closed = true;
}

OutputPin* Switch::getOutputPin()
{
	return &m_OutputPin;
}

InputPin* Switch::getInputPins()
{
	return nullptr;
}

int Switch::getInputPinNumber()
{
	return 0;
}

//virtual type getter function
string Switch::GetComponentType()
{
	return "Switch";
}
