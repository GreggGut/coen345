#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Grid.h"

using namespace std;

void action(string s, Grid* grid);

int main(int argc, const char * argv[])
{
//	bool programRunning = true;

	char in;
	vector<string> history;
	Grid* grid = NULL;

	do
	{
		string input;
		getline(std::cin, input);
		in = input[0];

		switch (in)
		{
		case 'h':
		case 'H':
			for (uint i = 0; i < history.size(); i++)
			{
				action(history.at(i), grid);
			}
			break;

		case 'i':
		case 'I':
		{
			delete grid;
			input.erase(0, 1);
			int gridSize = atoi(input.c_str());
			grid = new Grid(gridSize);

			break;
		}
		default:
			history.push_back(input);

			action(input, grid);
			break;

		}

	} while (in != 'q');

//	while (programRunning)
//	{
//
//	}

	return 0;
}

void action(string input, Grid* grid)
{
	char in = input[0];
	switch (in)
	{
	//Pen up
	case 'U':
	case 'u':
		grid->raisePen();
		break;
		//Pen down
	case 'D':
	case 'd':
		grid->lowerPen();
		break;

		//Turn right
	case 'R':
	case 'r':
		grid->turnRight();
		break;
		//Turn left
	case 'L':
	case 'l':
		grid->turnLeft();
		break;

		//Move x positions
	case 'M':
	case 'm':
	{
		input.erase(0, 1);
		int spacesToMove = atoi(input.c_str());

		int moved = grid->moveRobot(spacesToMove);
		if(moved !=spacesToMove)
		{

			cout<<"Error... moved "<<moved<<" tobemoved: "<<spacesToMove<<endl;
		}

		break;
	}
		//Print grid
	case 'P':
	case 'p':
		grid->print();

		break;

		//Current status
	case 'C':
	case 'c':
		grid->printRobot();

		break;

	default:
		break;
	}
}

/*
 [U|u]			Pen up
 [D|d]			Pen down
 [R|r]			Turn right
 [L|l]			Turn left
 [M s|m s]		Move forward s spaces (s is a non-negative integer)
 [P|p]			Print the N by N array and display the indices
 [C|c]			Print current position of the pen and whether it is up or down and its facing direction
 [Q|q]			Stop the program
 [I n|i n]		Initialize the system: The values of the array floor are zeros and the robot is back
 to [0, 0], pen up and facing north. n size of the array, an integer greater than zero
 [H|h]			Replay all the commands entered by the user as a history (bonus question 5 marks)
 */
