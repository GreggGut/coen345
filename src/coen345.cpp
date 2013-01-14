#include <iostream>
#include <stdlib.h>

using namespace std;

int** initGrid(int gridSize);
void deleteGrid(int** grid, int gridSize);
void displayGrid(int** grid, int gridSize);

int main(int argc, const char * argv[])
{
	bool programRunning = true;

	char in;

	int** grid;

	int gridSize = 10;

	int locX = 0, locY = 0;
	bool penDown = false;
	enum
	{
		face_north, face_west, face_south, face_east
	} facing = face_north;

	//Init
	grid = initGrid(gridSize);

	while (programRunning)
	{
		//get input
		//in = 'q';
		//get(&in);
		cin >> in;
		switch (in)
		{
		//Pen up
		case 'U':
		case 'u':
			penDown = false;
			break;
			//Pen down
		case 'D':
		case 'd':
			penDown = true;
			break;

			//Turn right
		case 'R':
		case 'r':
			facing = (facing == face_north ? face_east :
						facing == face_west ? face_north :
						facing == face_south ? face_west :
						facing == face_east ? face_south : facing);
			break;
			//Turn left
		case 'L':
		case 'l':
			facing = (facing == face_north ? face_west :
						facing == face_west ? face_south :
						facing == face_south ? face_east :
						facing == face_east ? face_north : facing);
			break;

			//Move (NYI)
//			case 'M':
//			case 'm':
//				break;

			//Print grid
		case 'P':
		case 'p':
			displayGrid(grid, gridSize);
			break;

			//Current status
		case 'C':
		case 'c':
			cout << "Pos: (" << locX << ", " << locY << ")" << endl;
			cout << "Facing: "
					<< (facing == face_north ? "north" :
						facing == face_west ? "west" :
						facing == face_south ? "south" :
						facing == face_east ? "east" : "Unknown direction")
					<< endl;
			cout << "Pen: " << (penDown ? "down" : "up") << endl;
			break;

			//Quit
		case 'Q':
		case 'q':
			programRunning = false;
			break;

			//Initialize grid (NYI)
//			case 'I':
//			case 'i':
//				break;

		default:
			break;
		}

		//react to input
		;
	}

	return 0;
}

int** initGrid(int gridSize)
{
	int** grid;

	grid = new int*[gridSize];
	for (int i = 0; i < gridSize; i++)
	{
		grid[i] = new int[gridSize];
		//Initialize all values to 0
		for (int j = 0; j < gridSize; j++)
		{
			grid[i][j] = 0;
		}
	}

	return grid;
}

void deleteGrid(int** grid, int gridSize)
{
	for (int i = 0; i < gridSize; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;

}

void displayGrid(int** grid, int gridSize)
{
	cout << endl;

	cout << "\t";
	for (int x = 0; x < gridSize; x++)
	{
		cout << x << "\t";
	}
	cout << endl;

	for (int y = gridSize - 1; y >= 0; y--)
	{
		cout << y << "\t";
		for (int x = 0; x < gridSize; x++)
		{
			if (grid[x][y])
				cout << '*';
			cout << "\t";
		}
		cout << y << endl;
	}

	cout << "\t";
	for (int x = 0; x < gridSize; x++)
	{
		cout << x << "\t";
	}
	cout << endl;
	cout << endl;

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
