#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include<fstream>

//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface

	int SelectedCount; //The number of selected components
	string Type; //the type of the temporary component
	string tempname;//the label of the temporary component
	void DeleteHelper(int I); //function to delete the component and its connection

	ofstream outputFile;//the output file used to save the window
	bool loadHelper;//boolen to know if the complist is empty or not 
					//false mean not empty
	int CCount;//counter to set the id of components (not connections)
	int lastID;//get the last ID of components before saving

public:	
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();

	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window


	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();


	//~~~~~~~~~~~~~~~~actions~~~~~~~~~~~~~~~~//
	//copy-cut-paste
	string getTypeofComponent();//function to return the type of the temporary component
	void setTemp(Component*);//function to set the type of the temporary component
	string getTemp();//function to return the label of the temporary component
	
	//delete 
	void DeleteComponents(); //function to delete all of the selected components
	void DeleteComponent(Component* C);//function to delete one component 

	//select
	void SelectComponent(Point ClickedPoint);//function to selete the component 

	//Simulate
	void Simulation();//function to simulate and test the program

	//Save
	void getSource_Target_and_InputPin(Connection* c, Component*& sourcegate, Component*& targetgate ,int& pinposition);
		//function to help saving the window by getting the source and the target pins of a connection
	void saveComponents();//function to save the component in the current window

	//Load
	void loadComponents(string l);//function to read the save file and load the components
	void getLoadData(string line, int index, string& ID, string& label, string& x, string& y);
													//read the line and return the data in it(label,type...)  
	void setLoadHelper(bool l);//set the load helper which know if the complist is empty or not 
	GraphicsInfo getLoadData(string& x, string& y, string& ID);//function to help getting the coordinates out of the save file
	Component* getComponentByID(int id);//return a component using its id
	void setLastID(int s);//set the last id

	//other usefull functions
	Component* getSelectedComponent(int x, int y);//return the component which in the range of the coming point
	Component* GetComponent(int index);//return the component using its index in the complist
	int GetComponentCount();//return the number of components in the complist
	bool ComponentHere(int x, int y);//function to know if there is any component in this range or no
	void ChangeModeHelper();//function to unselect all the selected components

	//FOR TRUTH TABLE
	int SearchForLEDs(Component**);
	int SearchForSwitches(Component**);

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);
	//destructor
	~ApplicationManager();
};

#endif