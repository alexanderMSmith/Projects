/**
 * @author Alexander Smith
 * @file maze.cpp
 * @brief This class
 *
 */

#include "maze.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
/**
 * @brief This method prints the maze into the console.
 *
 * @param Out The ostream that will contain the printed out maze contents.
 * @param Maze The maze that is going to be printed.
 * @return ostream& The ostream to be printed.
 */
ostream &operator<<(ostream &Out, const Maze &Maze) {
  for (int row = 0; row < Maze.Height; ++row) {
    for (int col = 0; col < Maze.Width; ++col) {
      Out << Maze.Field[row][col];
    }
    Out << endl;
  }
  Out << endl;
  return Out;
}

// For Clion, need the following line in CMakeLists.txt so maze.txt is found
// at the same location as the cpp files
// # need to load data files from current directory as cpp files
// set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
/**
 * @brief Construct a new Maze:: Maze object
 *
 * @param FileName The text file in which the maze contents is being created
 *  from.
 */
Maze::Maze(const string &FileName) {
  ifstream inFile;
  inFile.open(FileName);
  if (!inFile) {
    cout << "Unable to open file";
    exit(1); // terminate with error
  }
  inFile >> Width >> Height;
  inFile >> ExitRow >> ExitColumn;
  string str;
  getline(inFile, str);
  for (int row = 0; row < Height; ++row) {
    for (int col = 0; col < Width; ++col) {
      inFile.get(Field[row][col]);
      // cout << Row << ", " << col << ": " << field[Row][col] << endl;
    }
    getline(inFile, str);
  }
}
/**
 * @brief This method is a getter method that gets the exit row of the maze.
 *
 * @return int The exit row of the maze.
 */
int Maze::getExitRow() const { return ExitRow; }
/**
 * @brief This method is the getter method that gets the exit column of the maze
 *
 * @return int The exist column of the maze.
 */
int Maze::getExitColumn() const { return ExitColumn; }
/**
 * @brief This method checks to see if a given space is free or if is blocked
 *
 * @param Row The row position of the space that is being checked
 * @param Col The column position of the space that is being checked
 * @return true The way is clear.
 * @return false The way is obstructed.
 */
bool Maze::isClear(int mazeRow, int mazeCol) const {
  return Field[mazeRow][mazeCol] == ' ';
}
/**
 * @brief This method marks a spot on the maze as being part of a path.
 *
 * @param Row The row position of the space that will be marked.
 * @param Col The column position of the space that will be marked.
 */
void Maze::markAsPath(int mazeRow, int mazeCol) {
  Field[mazeRow][mazeCol] = '*';
}
/**
 * @brief This method marks a spot on the maze as being visited.
 *
 * @param Row The row position of the space that will be marked
 * @param Col The column position of hte space that will be marked
 */
void Maze::markAsVisited(int mazeRow, int mazeCol) {
  Field[mazeRow][mazeCol] = '+';
}
