#include "AddTruthTable.h"
#include<cmath>
#include<cstring>
#include<fstream>
#include "..\ApplicationManager.h"

AddTruthTable::AddTruthTable(ApplicationManager* pApp) :Action(pApp)
{
	for (int i = 0; i < 20; i++)
	{
		switches[i] = NULL;
	}
}

void AddTruthTable::Execute()
{

	int switchNo = pManager->SearchForSwitches(switches);
	int count = pow(2, switchNo);
	int power = pow(2, switchNo);;
	int c = 0;

	// fil in the inpute array
	for (int i = 0; i < switchNo; i++)
	{
		c = 0;
		for (int j = 0; j < power; j++)
		{
			for (int k = 0; k < count / 2; k++)
			{
				InputeArray[i][c++] = 0;
			}
			for (int k = count / 2; k < count; k++)
			{
				InputeArray[i][c++] = 1;
			}

		}
		count /= 2;
	}

	count = pow(2, switchNo);
	int LedNo = pManager->SearchForLEDs(led);

	//get status and fill in the output array
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < switchNo; j++)
		{
			if (InputeArray[j][i] == 1)
				switches[j]->setInputPinStatus(1, HIGH);

			else switches[j]->setInputPinStatus(1, LOW);
		}
		for (int k = 0; k < LedNo; k++)
		{
			pManager->Simulation();
			OutputeArray[k][i] = led[k]->GetInputPinStatus(1);
		}
	}
	DisplayTruthTable(switchNo, LedNo, count);
	Output* pOut = pManager->GetOutput();
	pOut->PrintMsg("Truth Table is created");


	//return the circuit to its last status before creating truth table
	for (int i = 0; i < switchNo; i++)
	{
		Switch* swt = static_cast<Switch*> (switches[i]);
		swt->setInputPinStatus(1, swt->getpreviousstatus());
	}
	pManager->Simulation();
}

void AddTruthTable::DisplayTruthTable(int switchNo, int LedNo, int count)
{
	ofstream print;
	print.open("TruthTable.txt", ios::out);
	int* switchlen = new int[switchNo]; //to adjust spaces between numbers in truth table input array
	int* LEDlen = new int[LedNo]; //to adjust spaces between numbers in truth table output array
	//display switches labels
	for (int j = 0; j < switchNo; j++)
	{
		string s = switches[j]->GetLabel();
		print << s << " ";
		switchlen[j] = s.length();
	}
	print << "\t\t";
	//display LEDs labels

	for (int j = 0; j < LedNo; j++)
	{
		string s = led[j]->GetLabel();
		print << s << " ";
		LEDlen[j] = s.length();
	}
	print << endl;
	//display the truth table
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < switchNo; j++)
		{
			for (int k = 0; k < (switchlen[j] - 1) / 2; k++)
				print << " ";
			print << InputeArray[j][i] << " ";
			for (int k = 0; k < (switchlen[j]) / 2; k++)
				print << " ";
		}
		print << "\t\t";
		for (int j = 0; j < LedNo; j++)
		{
			for (int k = 0; k < (LEDlen[j] - 1) / 2; k++)
				print << " ";
			print << OutputeArray[j][i] << " ";
			for (int k = 0; k < (LEDlen[j]) / 2; k++)
				print << " ";
		}

		print << endl;
	}
	print.close();
}

void AddTruthTable::ReadActionParameters()
{

}

void AddTruthTable::Undo()
{
}

AddTruthTable::~AddTruthTable(void)
{
}
void AddTruthTable::Redo()
{
}
