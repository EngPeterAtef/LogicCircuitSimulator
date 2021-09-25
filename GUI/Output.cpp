#include "Output.h"

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;

	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::DrawMSG(GraphicsInfo r_GfxInfo, string& string)
{
	pWind->DrawString(r_GfxInfo.x1, r_GfxInfo.y1, string);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::DrawsLabel(int x, int y, string label) 
{
	pWind->SetFont(15, PLAIN | BOLD, BY_NAME, "ARIAL");
	pWind->SetPen(BLUE);
	pWind->DrawString(x, y, label);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width , UI.height - UI.StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearToolBar() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

	ClearToolBar();

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_SIM] = "images\\Menu\\Menu_SIM.jpg";
	MenuItemImages[ITM_Add] = "images\\Menu\\Menu_Add.jpg";
	MenuItemImages[ITM_LED] = "images\\Menu\\LED_Driver.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\Menu\\switch-512.jpg";
	MenuItemImages[ITM_WIRE] = "images\\Menu\\WIRES.jpg";
	MenuItemImages[ITM_EDIT_CONN] = "images\\Menu\\Edit_Connection.jpg";
	MenuItemImages[ITM_SET_LABEL] = "images\\Menu\\Set_Label.jpg";
	MenuItemImages[ITM_EDIT_LABEL] = "images\\Menu\\Edit_Label.jpg";
	MenuItemImages[ITM_DELETE] = "images\\Menu\\DELETE.jpg";
	MenuItemImages[ITM_COPY] = "images\\Menu\\COPY.jpg";
	MenuItemImages[ITM_CUT] = "images\\Menu\\CUT.jpg";
	MenuItemImages[ITM_PASTE] = "images\\Menu\\PASTE.jpg";

	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_EXIT.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time

	for (int i = 0; i < ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], 0 + i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDesignADDBar() const
{
	UI.AppMode = DESIGN_ADD;	//Design Mode

	ClearToolBar();

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT2];
	MenuItemImages[ITM_TOOLS] = "images\\Menu\\Menu_Tools.jpg";
	MenuItemImages[ITM_AND2] = "images\\Menu\\AND.jpg";
	MenuItemImages[ITM_AND3] = "images\\Menu\\AND3.jpg";
	MenuItemImages[ITM_OR2] = "images\\Menu\\OR.jpg";
	MenuItemImages[ITM_OR3] = "images\\Menu\\OR3.jpg";
	MenuItemImages[ITM_NOT] = "images\\Menu\\NOT.jpg";
	MenuItemImages[ITM_BUFF] = "images\\Menu\\BUFFER.jpg";
	MenuItemImages[ITM_NAND2] = "images\\Menu\\NAND.jpg";
	MenuItemImages[ITM_NAND3] = "images\\Menu\\NAND3.jpg";
	MenuItemImages[ITM_NOR2] = "images\\Menu\\NOR.jpg";
	MenuItemImages[ITM_NOR3] = "images\\Menu\\NOR3.jpg";
	MenuItemImages[ITM_XOR2] = "images\\Menu\\XOR.jpg";
	MenuItemImages[ITM_XOR3] = "images\\Menu\\XOR3.jpg";
	MenuItemImages[ITM_XNOR2] = "images\\Menu\\XNOR.jpg";
	MenuItemImages[ITM_XNOR3] = "images\\Menu\\XNOR3.jpg";
	

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time

	for (int i = 0; i < ITM_DSN_CNT2; i++)
		pWind->DrawImage(MenuItemImages[i], 0 + i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	ClearToolBar();
	/////
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

	/////
	//done//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)
	string MenuItemImages[ITM_SIM_CNT];
	MenuItemImages[ITM_TOOLS] = "images\\Menu\\Menu_Tools.jpg";
	MenuItemImages[ITM_TRUTH] = "images\\Menu\\Menu_TruTab.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Menu\\Menu_SAVE.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Menu\\Menu_LOAD.jpg";
	MenuItemImages[ITM_EXIT2] = "images\\Menu\\Menu_EXIT.jpg";

	for (int i = 0; i < ITM_SIM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);

	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);

}

//TODO: Add similar functions to draw all components
void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR2.jpg";

	//Draw OR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR2.jpg";

	//Draw NOR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR2.jpg";

	//Draw NOR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}
void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XNOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR2.jpg";

	//Draw NOR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawBUFFER(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_Buff_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_Buff.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOT(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_INV_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_INV.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XNOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawSWITCH(GraphicsInfo r_GfxInfo, bool selected,bool closed) const
{
	string GateImage;
	if (UI.AppMode == DESIGN)
	{
		if (selected)	//use image in the highlighted case
			GateImage = "Images\\Gates\\SWITCH_HI.jpg";
		else
			GateImage = "Images\\Gates\\SWITCH.jpg";
	}
	else if (UI.AppMode == DESIGN_ADD)
	{
		if (selected)	//use image in the highlighted case
			GateImage = "Images\\Gates\\SWITCH_HI.jpg";
		else
			GateImage = "Images\\Gates\\SWITCH.jpg";
	}
	else if (UI.AppMode == SIMULATION)
	{
		if (selected)	//use image in the highlighted case
			GateImage = "Images\\Gates\\SWITCH_C.jpg";
		else
			GateImage = "Images\\Gates\\SWITCH.jpg";
	}
	
	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawLED(GraphicsInfo r_GfxInfo, bool selected,bool illu) const
{
	string GateImage;
	if (UI.AppMode == DESIGN)
	{
		if (selected)	//use image in the highlighted case
			GateImage = "Images\\Gates\\LED_HI.jpg";
		else
			GateImage = "Images\\Gates\\LED.jpg";
	}
	else if (UI.AppMode == DESIGN_ADD)
	{
		if (selected)	//use image in the highlighted case
			GateImage = "Images\\Gates\\LED_HI.jpg";
		else
			GateImage = "Images\\Gates\\LED.jpg";
	}
	else if (UI.AppMode == SIMULATION)
	{
		if (illu)	//use image in the highlighted case
			GateImage = "Images\\Gates\\LED_ON.jpg";
		else
			GateImage = "Images\\Gates\\LED.jpg";
	}
	
	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, 40, 43);
}

void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected, bool hi) const
{
	//TODO: Add code to draw connection
	if (UI.AppMode == SIMULATION)
	{
		if (hi)
		{
			pWind->SetPen(GREEN, 2.5);		//the connection is green if it is transmitting HIGH
		}
		else
		{
			pWind->SetPen(BLACK, 2.5);      //the connection is black if it is transmitting LOW
		}
	}
	else
	{
		if (selected)
			pWind->SetPen(RED, 2.5);         //the connection is red if it is selected
		else
			pWind->SetPen(BLACK, 2.5);
	}
	if (r_GfxInfo.x1 == r_GfxInfo.x2 || r_GfxInfo.y1 == r_GfxInfo.y2)
	{
		pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y2);
	}
	else
	{
		pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, (r_GfxInfo.x2 + r_GfxInfo.x1) / 2, r_GfxInfo.y1);
		pWind->DrawLine((r_GfxInfo.x2 + r_GfxInfo.x1) / 2, r_GfxInfo.y1, (r_GfxInfo.x2 + r_GfxInfo.x1) / 2, r_GfxInfo.y2);
		pWind->DrawLine((r_GfxInfo.x2 + r_GfxInfo.x1) / 2, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
	}
}



Output::~Output()
{
	delete pWind;
}
