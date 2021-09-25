#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
	Index = new int;
	LastClickedPoint = new Point;
}

void Input::GetPointClicked(int& x, int& y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output* pOut)
{
	///TODO: Implement this Function
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar
	char s[30] = " ";
	char empty[2] = " ";

	char c;
	int i = 0;
	if (UI.AppMode == DESIGN) {
		pWind->WaitKeyPress(c);
		if (c == '\x1' || c == '\r')
			return s;
		else
		{
			s[i] = c;
			i++;
			pOut->PrintMsg(s);
		}

		pWind->WaitKeyPress(c);
		while (c != '\r')
		{
			if (c == '\b')
			{
				if (i > 0)
					i--;
				s[i] = '\0';
				pOut->PrintMsg(s);
			}
			else if (c == '\x1')
			{
				return empty;
			}
			else
			{
				s[i] = c;
				i++;
				pOut->PrintMsg(s);
			}
			pWind->WaitKeyPress(c);
		}

	}
	s[i] = '\0';
	return s;
}
string Input::GetSrting(Output* pOut, string priv)
{
	///TODO: Implement this Function
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar
	char s[30];
	int in;
	for (int i = 0; i < priv.length(); i++)
	{
		s[i] = priv[i];
		in = i;
	}
	for (int i = in+1; i < 30; i++)
		s[i] = '\0';
	
	char empty[2] = " ";

	char c;
	int i = priv.length();
	if (UI.AppMode == DESIGN) {
		pWind->WaitKeyPress(c);
		if (c == '\x1' || c == '\r')
			return s;
		else
		{
			s[i] = c;
			i++;
			pOut->PrintMsg(s);
		}

		pWind->WaitKeyPress(c);
		while (c != '\r')
		{
			if (c == '\b')
			{
				if (i > 0)
					i--;
				s[i] = '\0';
				pOut->PrintMsg(s);
			}
			else if (c == '\x1')
			{
				return empty;
			}
			else
			{
				s[i] = c;
				i++;
				pOut->PrintMsg(s);
			}
			pWind->WaitKeyPress(c);
		}

	}
	s[i] = '\0';
	return s;
}
//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

     LastClickedPoint->x = x ;
     LastClickedPoint->y = y ;

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			*Index = ClickedItemOrder;
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_Add: return CHANGE_MODE;
			case ITM_SIM: return CHANGE_MODE;
			case ITM_WIRE: return ADD_CONNECTION;
			case ITM_EDIT_CONN: return Edit_CONNECTION;
			case ITM_LED: return ADD_LED;
			case ITM_SWITCH: return ADD_Switch;
			case ITM_SET_LABEL: return ADD_Label;
			case ITM_EDIT_LABEL: return EDIT_Label;
			case ITM_DELETE: return DEL;
			case ITM_COPY: return COPY;
			case ITM_CUT: return CUT;
			case ITM_PASTE: return PASTE;
			case ITM_EXIT: return EXIT;
			default: return DSN_TOOL; 	//A click on empty place in desgin toolbar
			}

		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else if (UI.AppMode == DESIGN_ADD)
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			*Index = ClickedItemOrder;
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_TOOLS_ADD: return CHANGE_MODE;
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_AND3: return ADD_AND_GATE_3;
			case ITM_OR3: return ADD_OR_GATE_3;
			case ITM_NOT: return ADD_INV;
			case ITM_BUFF: return ADD_Buff;
			case ITM_NAND2: return ADD_NAND_GATE_2;
			case ITM_NAND3: return ADD_NAND_GATE_3;
			case ITM_NOR2: return ADD_NOR_GATE_2;
			case ITM_NOR3: return ADD_NOR_GATE_3;
			case ITM_XOR2: return ADD_XOR_GATE_2;
			case ITM_XOR3: return ADD_XOR_GATE_3;
			case ITM_XNOR2: return ADD_XNOR_GATE_2;
			case ITM_XNOR3: return 	ADD_XNOR_GATE_3;
			default: return DSN_TOOL; 	//A click on empty place in desgin toolbar
			}

		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{
		if (y >= 0 && y < UI.ToolBarHeight) {

			int ClickedItemOrder = (x / UI.ToolItemWidth);
			*Index = ClickedItemOrder;

			switch (ClickedItemOrder) {
			case ITM_TOOLS: return CHANGE_MODE;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_TRUTH: return Create_TruthTable;
			case ITM_EXIT2: return EXIT;

			default: return DSN_TOOL;
			}

		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
		//This should be changed after creating the compelete simulation bar 
	}

}

ActionType Input::GetMode() const {
	if (UI.AppMode == DESIGN)
	{
		switch (*Index)
		{
		case ITM_Add: return DSN_MODE_ADD;
		case ITM_SIM: return SIM_MODE;
		default: return DSN_TOOL;
		}
	}
	else if (UI.AppMode == DESIGN_ADD)
	{
		switch (*Index)
		{
		case ITM_TOOLS_ADD: return DSN_MODE;
		default: return DSN_TOOL;
		}
	}
	else
	{
		switch (*Index)
		{
		case ITM_TOOLS: return DSN_MODE;
		default: return DSN_TOOL;
		}
	}

}

	

Point Input::GetLastClicked()
{
	return *LastClickedPoint;
}
Input::~Input()
{

}
