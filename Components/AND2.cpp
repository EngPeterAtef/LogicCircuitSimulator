#include "AND2.h"

AND2::AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void AND2::Operate()
{

	int first = m_InputPins[0].getStatus();
	int second = m_InputPins[1].getStatus();
	//caclulate the output status as the ANDing of the two input pins
	if (first == 1 && second == 1 )
		m_OutputPin.setStatus(HIGH);

	else m_OutputPin.setStatus(LOW);
	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void AND2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	if (m_GfxInfo.y1 > UI.ToolBarHeight && m_GfxInfo.y2 < UI.height - UI.StatusBarHeight)
	{
		pOut->DrawAND2(m_GfxInfo,select);
	}

}

//returns status of outputpin
int AND2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int AND2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void AND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

string AND2::GetComponentType()
{
	return "AND2";
}


