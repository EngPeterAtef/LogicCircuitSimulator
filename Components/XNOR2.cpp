#include "XNOR2.h"

XNOR2::XNOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void XNOR2::Operate()
{
	//caclulate the output status as the ANDing of the two input pins
	STATUS first = m_InputPins[0].getStatus();
	STATUS second = m_InputPins[1].getStatus();
	STATUS out1;

	if (first != second)
		out1 = HIGH;
	else out1 = LOW;

	if (out1 == HIGH)
		m_OutputPin.setStatus(LOW);
	else m_OutputPin.setStatus(HIGH);

	//Add you code here
}


// Function Draw
// Draws 2-input XNOR gate
void XNOR2::Draw(Output* pOut)
{

	if (m_GfxInfo.y1 > UI.ToolBarHeight && m_GfxInfo.y2 < UI.height - UI.StatusBarHeight)
	{
		pOut->DrawXNOR2(m_GfxInfo, select);
	}

	//Call output class and pass gate drawing info to it.
	//pOut->DrawAND2(m_GfxInfo);
}

//returns status of outputpin
int XNOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XNOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XNOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

string XNOR2::GetComponentType()
{
	return "XNOR2";
}
