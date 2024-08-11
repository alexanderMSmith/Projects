/**
* @author Alexander Smith
* @file creature.h
* @brief This is the header file for the creature class. The class's purpose 
*   is to solve mazes, using backtracking if necessary, and record the path
*   taken.
*
*/


#ifndef ASS3_CREATURE_H
#define ASS3_CREATURE_H

#include "maze.h"
#include <ostream>

class Creature {
public:
  friend ostream &operator<<(ostream &Out, const Creature &Creature);

private:
  int row;
  int col;
  int *movesAttempted = new int[101]; // Keeps track of how many move options
                                      // are available
  int moveSlot = 0;        // An iterator to track where on the path we are.
  string *moveList = new string[101]; // Lists the paths taken so far.

public:
  Creature(int Row, int Col); //The Creature constructor
  string solve(Maze &Maze); //The recursive method creature uses to solve mazes
  bool atExit(const Maze &Maze) const; //Checks if the exit was reached
  string goNorth(Maze &Maze); //Takes the creature north
  string goSouth(Maze &Maze); //Takes the creature south
  string goEast(Maze &Maze); //Takes the creature east
  string goWest(Maze &Maze); //Takes the creature west.
  void goNorthBacktracking(Maze &Maze); //Takes creature north by backtracking
  void goSouthBacktracking(Maze &Maze);//Takes creature south by backtracking
  void goEastBacktracking(Maze &Maze);//Takes creatures east by backtracking
  void goWestBacktracking(Maze &Maze);//Takes creature west by backtracking

};

#endif //ASS3_CREATURE_H