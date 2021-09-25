#include "InputPin.h"

InputPin::InputPin()
{
	connected = false;
}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent()
{
	return pComp;
}

void InputPin::setConnected(bool c)
{
	connected = c;
}

bool InputPin::getConnected()
{
	return connected;
}
