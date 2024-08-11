/**
* @author Alexander Smith
* @file maze.h
* @brief This is the header class for the maze class. The Maze class creates
*   a maze to be navigated and contains functions for checking the mazes
*   exit and marking paths.
*
*/


#ifndef ASS3_MAZE_H
#define ASS3_MAZE_H

#include <ostream>

using namespace std;

enum CELL { CLEAR, WALL, PATH, VISITED };

class Maze {
  friend ostream &operator<<(ostream &Out, const Maze &Maze); //Prints out the
    //maze
private:
  const static int MAX_SIZE = 100; //Declares the max size for columns and 
    //rows to be 100
  char Field[MAX_SIZE][MAX_SIZE]; //Creates a 2D array of the max size
  int Width, Height; //The Width and Height of the maze
  int ExitRow, ExitColumn; //The exit row and column of the maze
public:
  explicit Maze(const string &FileName); //Constructor for the maze
  bool isClear(int mazeRow, int mazeCol) const; //Checks to see if a spot if is
    //empty
  void markAsPath(int mazeRow, int mazeCol); //Marks spot as being part of the 
    //solution
  void markAsVisited(int mazeRow, int mazeCol); //Marks spot as being visited
  int getExitRow() const; //Getter method for the exit row
  int getExitColumn() const; //Getter method for the exit column

};

#endif //ASS3_MAZE_H
