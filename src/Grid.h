/*
 * Grid.h
 *
 *  Created on: Jan 21, 2013
 *      Author: k_berson
 */

#ifndef GRID_H_
#define GRID_H_

class Grid
{
public:
	// [I n|i n] Initialize the system: The values of the array floor are zeros and the robot is back to [0, 0], pen up and facing north. n size of the array, an integer greater than zero
	Grid(int gridSize);
	virtual ~Grid();

	//
	void raisePen();				// [U|u] Pen up
	void lowerPen();				// [D|d] Pen down
	void turnRight();				// [R|r] Turn right
	void turnLeft();				// [L|l] Turn left
	int moveRobot(int distance);	// [M s|m s] Move forward s spaces (s is a non-negative integer)
	void print();					// [P|p] Print the N by N array and display the indices
	void printRobot();				// [C|c] Print current position of the pen and whether it is up or down and its facing direction

private:
	int size;
	int** contents;

	struct
	{
		int x, y;
		bool penDown;
		enum
		{
			FACING_NORTH, FACING_WEST, FACING_SOUTH, FACING_EAST
		} facing;
	} robot;

	//
	void markSpace(int x, int y);


};


/*
 [U|u] Pen up
 [D|d] Pen down
 [R|r] Turn right
 [L|l] Turn left
 [M s|m s] Move forward s spaces (s is a non-negative integer)
 [P|p] Print the N by N array and display the indices
 [C|c] Print current position of the pen and whether it is up or down and its facing direction
 [Q|q] Stop the program
 [I n|i n] Initialize the system: The values of the array floor are zeros and the robot is back
 to [0, 0], pen up and facing north. n size of the array, an integer greater than zero
 [H|h] Replay all the commands entered by the user as a history (bonus question 5 marks)
 */


#endif /* GRID_H_ */
