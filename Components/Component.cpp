#include "Component.h"

Component::Component(const GraphicsInfo& r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;
	select = false;
	m_Label = " ";
	ID = 0;
}
bool Component::InRange(int x, int y)
{

	if (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2)
	{
		if (y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2)
		{
			return true;
		}
	}
	return false;
}

bool Component::InRange2(int x, int y)
{

	if (x >= m_GfxInfo.x1 - 35 && x <= m_GfxInfo.x2 + 35)
	{
		if (y >= m_GfxInfo.y1 - 24 && y <= m_GfxInfo.y2 + 24)
		{
			return true;
		}
	}
	return false;
}

void Component::SetSelected(bool selected)
{

	select = selected;
}

bool Component::IsSelected()
{
	return select;
}

string Component::GetLabel()
{
	return m_Label;
}

void Component::SetLabel(string label)
{
	m_Label = label;
}

GraphicsInfo Component::getCoordinates()
{
	return m_GfxInfo;
}


void Component::setID(int x)
{
	ID = x;
}

int Component::getID() const
{
	return ID;
}

Component::Component()
{
	select = false;
	m_Label = " ";
}

Component::~Component()
{}

