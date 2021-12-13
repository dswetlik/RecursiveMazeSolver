/*
 * Diedrich Swetlik
 * Terry Hostetler
 * CS-215 Data Structures
 * 9/6/2020
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// constant ints for use in array declaration.
const int MAX_ROW = 10, MAX_COL = 10;

// opens maze.in.txt file
void OpenFile(ifstream& file, string fileName);
// reads in maze file, if opened by OpenFile, into a 2D array
void ReadMazeFile(ifstream& file);
// recursively searches 2D array from start to goal
bool RecursiveSearch(char maze[][MAX_COL], int rowSize, int colSize, int xPos, int yPos, int moves);
// uses moves from RecursiveSearch to return a char in alphabetical order
char AssignChar(int n);

int main()
{
	ifstream mazeFile;

	OpenFile(mazeFile, "maze.in");

	ReadMazeFile(mazeFile);
}

// opens maze.in.txt file
void OpenFile(ifstream& file, string fileName)
{
	// attempting to open file
	file.open(fileName);

	// if file is null, exit the program
	if (!file)
	{
		cout << "Could not open " << fileName << endl;
		exit(1);
	}
}

// reads in maze file, if opened by OpenFile, into a 2D array
void ReadMazeFile(ifstream& file)
{
	// ints to hold numbers from file
	int NR, NC;
	// char to hold chars from file
	char x;
	// reading in number of rows and columns
	file >> NR >> NC;

	// if rows and columns are greater than the max, exit program
	if (NR > MAX_ROW || NC > MAX_COL)
	{
		cout << "Out of Bounds: Either Rows or Columns are too large!\n";
		exit(2);
	}

	// declaration of 2D array
	char maze[MAX_ROW][MAX_COL];

	// parsing through file and assigning chars into the array
	for (int i = 0; i < NR; i++)
	{
		for (int j = 0; j < NC; j++)
		{
			file >> x;
			maze[i][j] = x;
			cout << x;
		}
		cout << endl;
	}

	cout << "Maze Loaded; Starting Search..." << endl;

	// start of recursive search
	if (RecursiveSearch(maze, NR - 1, NC - 1, 0, 0, 0))
		cout << "Maze Successfully Completed!\n";
	else
		cout << "Maze Failed to Complete.\n";

	// final print out of maze
	for (int i = 0; i < NR; i++)
	{
		for (int j = 0; j < NC; j++)
		{
			cout << maze[i][j];
		}
		cout << endl;
	}

}

// recursively searches 2D array from start to goal
bool RecursiveSearch(char maze[][MAX_COL], int rSize, int cSize, int xPos, int yPos, int moves)
{

	// BASE CASES

	// checks if x and y position is outside of maze
	if ((xPos > rSize || yPos > cSize) || (xPos < 0 || yPos < 0)) return false;
	// checks to see if position in maze is an open cell
	if (maze[xPos][yPos] != '.') return false;
	// since x and y position is valid, assigns a char to the cell
	maze[xPos][yPos] = AssignChar(moves);
	// increases char in alphabet by one
	moves += 1;
	// checks to see if x and y position is at the goal
	if (rSize == xPos && cSize == yPos) return true;

	// GENERAL CASES

	// checks cases of maze[xPos][yPos + 1] 
	if (RecursiveSearch(maze, rSize, cSize, xPos, yPos + 1, moves)) return true;
	// checks cases of maze[xPos + 1][yPos]
	if (RecursiveSearch(maze, rSize, cSize, xPos + 1, yPos, moves)) return true;
	// checks cases of maze[xPos][yPos - 1]
	if (RecursiveSearch(maze, rSize, cSize, xPos, yPos - 1, moves)) return true;
	// checks cases of maze[xPos - 1][yPos]
	if (RecursiveSearch(maze, rSize, cSize, xPos - 1, yPos, moves)) return true;

	// removes char from cell if recursion falls through all general cases
	maze[xPos][yPos] = '.';
	return false;
}

// uses moves from RecursiveSearch to return a char in alphabetical order
char AssignChar(int n)
{
	// creates alphabet string
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	// returns char at n mod 26, % is used to have wrap around from z to a
	return alphabet[n % 26];
}