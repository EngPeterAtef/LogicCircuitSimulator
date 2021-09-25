#include "Load.h"
#include "..\ApplicationManager.h"


Load::Load(ApplicationManager* pApp) :Action(pApp)
{

}

void Load::Execute()
{
	ifstream input;
	int count = 1;

	//open the savefile
	input.open("SaveFile.txt");

	if (input.is_open())
	{
		//read from the file line by line neglecting the first and last line using the count 
		string line;
		while (!input.eof())
		{
			getline(input, line);
			if (count != 1 && line != "-1")
				pManager->loadComponents(line);
			else if (count == 1)
				pManager->setLastID(stoi(line));
			count++;
		}
		input.close();
	}

	pManager->setLoadHelper(false);

}


void Load::ReadActionParameters()
{
}

void Load::Undo()
{
}

void Load::Redo()
{
}
