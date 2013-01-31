/**  Created on: Jan 20, 2013
 *      Author: Grzegorz Gut
 */
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Grid.h"

using namespace std;

void action(string s, Grid* grid);
Grid* initialize(Grid* grid, int gridSize);
int getGridSize(string input);
int analyseInput(string input);

int main()
{
	char in;
	vector<string> history;
	Grid* grid = NULL;

	//Making sure the grid is initialize before being able to use it
	//The only options available are initialization of the grid (I n|i n), where n is a positive integer and quit with (Q|q)
	while (grid == NULL)
	{
		string input;
		cout << "Enter command: ";
		getline(std::cin, input);
		in = input[0];

		//Initializing the grid
		if (input[0] == 'i' || input[0] == 'I')
		{
			history.push_back(input);
			int gridSize;
			if ((gridSize = getGridSize(input)) > 0)
			{
				grid = initialize(grid, gridSize);
			}
		}
		//Quitting
		else if (input[0] == 'q' || input[0] == 'Q')
		{
			break;
		}
		else
		{
			history.push_back(input);
			cout << "You need to initialize the board first." << endl
					<< "Use command 'I' followed by the floor size." << endl;
		}
	}

	//Loop until user wants to quit
	while (in != 'q')
	{
		string input;
		cout << "Enter command: ";
		getline(std::cin, input);
		in = input[0];

		switch (in)
		{
		//History
		case 'h':
		case 'H':
			//Replay every event in the history
			for (uint i = 0; i < history.size(); i++)
			{
				cout << history.at(i) << endl;
				if (history.at(i)[0] == 'i' || history.at(i)[0] == 'I')
				{
					string input = history.at(i);
					int gridSize;
					if ((gridSize = getGridSize(input)) > 0)
					{
						grid = initialize(grid, gridSize);
					}
				}
				else
				{
					action(history.at(i), grid);
				}
			}
			break;
			//Initializing board
		case 'i':
		case 'I':
		{
			history.push_back(input);

			int gridSize;
			if ((gridSize = getGridSize(input)) > 0)
			{
				grid = initialize(grid, gridSize);
			}

			break;
		}
			//Any other entry
		default:
			history.push_back(input);

			action(input, grid);
			break;
		}
	}
	cout<<"Quitting..."<<endl;

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
		//Analyze input and move robot if input is fine
		int spacesToMove = analyseInput(input);
		if (spacesToMove > -1)
		{
			//Try moving and display error message if the move cannot be completed (request move doesn't equal real move)
			int moved = grid->moveRobot(spacesToMove);
			if (moved != spacesToMove)
			{

				cout << "Error... Requested a move of " << spacesToMove
						<< " spaces however the robot was only able to move "
						<< moved << " space(s)" << endl;
			}
		}
		else
		{
			cout
					<< "Error... The Move command needs to be in the following format:"
					<< endl
					<< "nM i|m i|Mi|mi, where i is a non negative integer."
					<< endl;
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
	case 'q':
	case 'Q':
		break;

		//Not a valid command
	default:
		cout << input << " is not a valid command" << endl;
		break;
	}
}

//Initialize the board to a new size
Grid* initialize(Grid* grid, int gridSize)
{
	delete grid;

	grid = new Grid(gridSize);
	return grid;
}

//Get board size from user input
int getGridSize(string input)
{
	int size;
	if ((size = analyseInput(input)) > 0)
	{
		return size;
	}
	else
	{
		cout
				<< "Error... The Initialize command needs to be in the following format: \nI n|i n|In|in, where n is a positive integer."
				<< endl;
		return -1;
	}
}

//Analyze the user input with the Initialize and Move commands
int analyseInput(string input)
{
	//Remove all leading whitespace
	input.erase(0, 1);
	int lead = 0;
	for (uint i = 0; i < input.length(); i++)
	{
		if (!(input[i] == ' ' || input[i] == '\t' || input[i] == '\n'))
		{
			lead = i;
			break;
		}
	}
	input.erase(0, lead);

	//Making sure there is at least 1 integer/character in the user input
	if (input.length() == 0)
	{
		return -1;
	}

	//Making sure that the input contains only integers (after the command)
	for (uint i = 0; i < input.length(); i++)
	{
		if (input[i] < 48 || input[i] > 57)
		{
			return -1;
		}
	}
	return atoi(input.c_str());
}
