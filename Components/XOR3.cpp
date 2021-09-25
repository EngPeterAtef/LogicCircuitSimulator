
#include "XOR3.h"


XOR3::XOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void XOR3::Operate()
{
	//caclulate the output status as the ANDing of the two input pins
	STATUS first = m_InputPins[0].getStatus();
	STATUS second = m_InputPins[1].getStatus();
	STATUS third = m_InputPins[2].getStatus();
	STATUS out1;

	if (first != second)
		out1 = HIGH;
	else out1 = LOW;

	if (out1 != third)
		m_OutputPin.setStatus(HIGH);
	else m_OutputPin.setStatus(LOW);


	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void XOR3::Draw(Output* pOut)
{

	if (m_GfxInfo.y1 > UI.ToolBarHeight && m_GfxInfo.y2 < UI.height - UI.StatusBarHeight)
	{
		pOut->DrawXOR3(m_GfxInfo, select);
	}

	//Call output class and pass gate drawing info to it.
	//pOut->DrawAND2(m_GfxInfo);
}

//returns status of outputpin
int XOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

string XOR3::GetComponentType()
{
	return "XOR3";
}
