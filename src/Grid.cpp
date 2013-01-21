/*
 * Grid.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: k_berson
 */

//Self
#include "Grid.h"
//C Library
#include <iostream>


//namespace
using namespace std;


//Constructor
// [I n|i n] Initialize the system: The values of the array floor are zeros and the robot is back to [0, 0], pen up and facing north. n size of the array, an integer greater than zero
Grid::Grid(int gridSize)
{
  size = gridSize;

	//robot init
	robot.facing = robot.FACING_NORTH;
	robot.penDown = false;
	robot.x = 0;
	robot.y = 0;


	contents = new int*[gridSize];
	for (int i = 0; i < gridSize; i++)
	{
		contents[i] = new int[gridSize];
		//Initialize all values to 0
		for (int j = 0; j < gridSize; j++)
		{
			contents[i][j] = 0;
		}
	}

}


//Destructor
Grid::~Grid()
{
	for (int i = 0; i < size; i++) {
		delete[] contents[i];
	}
	delete[] contents;
}


/*----------------------------------------------------*/
/*- Private                                          -*/
/*----------------------------------------------------*/

//Marks a space if within bounds
void Grid::markSpace(int x, int y)
{
	if (x >= 0 && x < size && y >= 0 && y < size)
		contents[x][y] = 1;
}


/*----------------------------------------------------*/
/*- Public                                           -*/
/*----------------------------------------------------*/

//Raise pen
// [U|u] Pen up
void Grid::raisePen()
{
	robot.penDown = false;
}


//Lower pen
// [D|d] Pen down
void Grid::lowerPen()
{
	robot.penDown = true;
}


//Turn robot right
// [R|r] Turn right
void Grid::turnRight()
{
	robot.facing = (robot.facing == robot.FACING_NORTH ? robot.FACING_EAST :
			robot.facing == robot.FACING_WEST ? robot.FACING_NORTH :
			robot.facing == robot.FACING_SOUTH ? robot.FACING_WEST :
			robot.facing == robot.FACING_EAST ? robot.FACING_SOUTH :
												robot.facing);
}


//Turn robot left
// [L|l] Turn left
void Grid::turnLeft()
{
	robot.facing = (robot.facing == robot.FACING_NORTH ? robot.FACING_WEST :
			robot.facing == robot.FACING_WEST ? robot.FACING_SOUTH :
			robot.facing == robot.FACING_SOUTH ? robot.FACING_EAST :
			robot.facing == robot.FACING_EAST ? robot.FACING_NORTH :
												robot.facing);
}


//Move robot
// [M s|m s] Move forward s spaces (s is a non-negative integer)
int Grid::moveRobot(int distance)
{
	int distMoved = 0;

	int xDirn = (robot.facing == robot.FACING_WEST ? -1 :
					robot.facing == robot.FACING_EAST ? 1 :
														0);
	int yDirn = (robot.facing == robot.FACING_SOUTH ? -1 :
					robot.facing == robot.FACING_NORTH ? 1 :
														0);

	//mark starting space (even if not moving)
	this->markSpace(robot.x, robot.y);

	//move 1 space at a time
	//check bounds before moving
	while (distMoved < distance
			&& (robot.x >= 1 && robot.x < size-1)
			&& (robot.y >= 1 && robot.y < size-1)
	)
	{
		//move into next space
		robot.x += xDirn;
		robot.y += yDirn;
		distMoved++;
		//mark new space
		this->markSpace(robot.x, robot.y);
	}

	return distMoved;
}


//Print grid
// [P|p] Print the N by N array and display the indices
void Grid::print()
{
	cout << endl;

	cout << "\t";
	for (int x = 0; x < size; x++) {
		cout << x << "\t";
	}
	cout << endl;

	for (int y = size - 1; y >= 0; y--) {
		cout << y << "\t";
		for (int x = 0; x < size; x++) {
			if (contents[x][y] == 1)
				cout << '*';
			cout << "\t";
		}
		cout << y << endl;
	}

	cout << "\t";
	for (int x = 0; x < size; x++) {
		cout << x << "\t";
	}
	cout << endl;

	cout << endl;

}


//Print robot position
// [C|c] Print current position of the pen and whether it is up or down and its facing direction
void Grid::printRobot()
{
	cout << "Pos: (" << robot.x << ", " << robot.y << ")" << endl;
	cout  << "Facing: "
			<< (robot.facing == robot.FACING_NORTH ? "north" :
				robot.facing == robot.FACING_WEST ? "west" :
				robot.facing == robot.FACING_SOUTH ? "south" :
				robot.facing == robot.FACING_EAST ? "east" :
													"Unknown direction")
			<< endl;
	cout << "Pen: " << (robot.penDown ? "down" : "up") << endl;

}


