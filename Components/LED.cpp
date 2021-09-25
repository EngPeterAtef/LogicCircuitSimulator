
#include "LED.h"

LED::LED(const GraphicsInfo& r_GfxInfo)//need to do the connect part
{
    m_GfxInfo.x1 = r_GfxInfo.x1;
    m_GfxInfo.y1 = r_GfxInfo.y1;
    m_GfxInfo.x2 = r_GfxInfo.x2;
    m_GfxInfo.y2 = r_GfxInfo.y2;
    //Associate all input pins to this gate
    m_InputPins.setComponent(this);
    light = false;
    ID = 0;
}

void LED::Operate()
{
    if (GetInputPinStatus() == LOW)
        light = false;
    else
        light = true;
}

void LED::Draw(Output* pOut)
{
    if (m_GfxInfo.y1 > UI.ToolBarHeight && m_GfxInfo.y2 < UI.height - UI.StatusBarHeight)
        pOut->DrawLED(m_GfxInfo, select, light);

}

int LED::GetOutPinStatus()
{
    return -1;
}

int LED::GetInputPinStatus(int n)
{
    return m_InputPins.getStatus();
}

void LED::setInputPinStatus(int n, STATUS s)
{
    m_InputPins.setStatus(s);
}

OutputPin* LED::getOutputPin()
{
    return NULL;
}

InputPin* LED::getInputPins()
{
   return &m_InputPins;
}

int LED::getInputPinNumber()
{
    return 1;
}

string LED::GetComponentType()
{
    return "LED";
}
