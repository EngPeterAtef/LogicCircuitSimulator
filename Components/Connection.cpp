#include "Connection.h"


Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin):Component(r_GfxInfo)
{
	SrcPin = pSrcPin;
	DstPin = pDstPin;
	High = false;
}
void Connection::setSourcePin(OutputPin *pSrcPin)
{	SrcPin = pSrcPin;	}

OutputPin* Connection::getSourcePin()
{	return SrcPin;	}


void Connection::setDestPin(InputPin *pDstPin)
{	DstPin = pDstPin;	}

InputPin* Connection::getDestPin()
{	return DstPin;	}


void Connection::Operate()
{
	//Status of connection destination pin = status of connection source pin
	DstPin->setStatus((STATUS)SrcPin->getStatus());
	if (SrcPin->getStatus() == HIGH)
	{
		High = true;
	}
	else
	{
		High = false;
	}
}

void Connection::Draw(Output* pOut)
{
	pOut->DrawConnection(m_GfxInfo,select,High);
}

int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return DstPin->getStatus();
}


int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}


InputPin* Connection::getInputPins()
{
	return NULL;
}
int Connection::getInputPinNumber()
{
	return 1;
}

string Connection::GetComponentType()
{
	return "Connection";
}

bool Connection::InRange(int x, int y)
{
	//condition on the horizontal coordinates
	if ((x >= m_GfxInfo.x1 && x <= (m_GfxInfo.x1 + m_GfxInfo.x2) / 2) && (y >= m_GfxInfo.y1 - 2 && y <= m_GfxInfo.y1 + 2)
		|| (x >= (m_GfxInfo.x1 + m_GfxInfo.x2) / 2 - 3 && x <= (m_GfxInfo.x1 + m_GfxInfo.x2) / 2 + 3)
		|| (x >= (m_GfxInfo.x1 + m_GfxInfo.x2) / 2) && x <= m_GfxInfo.x2 && (y >= m_GfxInfo.y2 - 2 && y <= m_GfxInfo.y2 + 2))
	{
		//condition on the vertical coordinates
		if (m_GfxInfo.y1 > m_GfxInfo.y2 && (y <= m_GfxInfo.y1 && y >= m_GfxInfo.y2)) //case 1: source gate is below destination gate
		{
			return true;
		}
		if (m_GfxInfo.y1 < m_GfxInfo.y2 && (y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2)) //case 2: source gate is above destination gate
		{
			return true;
		}
	}
	return false;
}
bool Connection::InRange2(int x, int y)
{
	if ((x >= m_GfxInfo.x1 && x <= (m_GfxInfo.x1 + m_GfxInfo.x2) / 2) && (y >= m_GfxInfo.y1 - 24 && y <= m_GfxInfo.y1 + 24)
		|| (x >= (m_GfxInfo.x1 + m_GfxInfo.x2) / 2 - 35 && x <= (m_GfxInfo.x1 + m_GfxInfo.x2) / 2 + 35)
		|| (x >= (m_GfxInfo.x1 + m_GfxInfo.x2) / 2) && x <= m_GfxInfo.x2 && (y >= m_GfxInfo.y2 - 24 && y <= m_GfxInfo.y2 + 24))
	{
		if (m_GfxInfo.y1 > m_GfxInfo.y2 && (y <= m_GfxInfo.y1 && y >= m_GfxInfo.y2)) //case 1: source gate is below destination gate
		{
			return true;
		}
		if (m_GfxInfo.y1 < m_GfxInfo.y2 && (y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2)) //case 2: source gate is above destination gate
		{
			return true;
		}
	}
	return false;
}

OutputPin* Connection::getOutputPin()
{
	return NULL;
}

