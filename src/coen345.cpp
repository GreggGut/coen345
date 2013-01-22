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

int main(int argc, const char * argv[])
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

		if (input[0] == 'i' || input[0] == 'I')
		{
			history.push_back(input);
			int gridSize;
			if ((gridSize = getGridSize(input)) > 0)
			{
				grid = initialize(grid, gridSize);
			}
		}
		else if (input[0] == 'q' || input[0] == 'Q')
		{
			break;
		}
		else
		{
			cout
					<< "You need to initialize the system first. Use command 'I' followed by the floor size."
					<< endl;
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
		case 'h':
		case 'H':
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
		default:
			history.push_back(input);

			action(input, grid);
			break;
		}
	}

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
		if (spacesToMove > -1)
		{

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
			cout << "The move can only accept non-negative integer" << endl;
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

		//Not a valid command
	default:
		cout << input << " is not a valid command" << endl;
		break;
	}
}

Grid* initialize(Grid* grid, int gridSize)
{
	delete grid;

	grid = new Grid(gridSize);
	return grid;
}

int getGridSize(string input)
{
	input.erase(0, 1);
	int gridSize = atoi(input.c_str());
	if (gridSize < 1)
	{
		cout << "Grid size needs to be larger than 0" << endl;
	}
	return gridSize;
}
