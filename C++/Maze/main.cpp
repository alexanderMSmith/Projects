/*
 * @author Alexander Smith
 * @file main.cpp
 *
 * This file is the driver method for the creature and maze classes.
 * It esnures each line of code is reached and every method is runned.
 */

#include <iostream>

#include "creature.h"

/**
 * @brief This method tests the Maze and Creature objects by using creature
 * to solve 3 different mazes, each with a different exit and requiring
 * different amounts of backtracking
 *
 */
void test() {
  Maze maze1("maze.txt");  // Base case maze, no backtracking needed.
  Maze maze2("maze2.txt"); // Maze requiring backtracking to solve.
  Maze maze3(
      "maze3.txt"); // Ensures all backtracking methods are tested and
                    // the creature can explore from the starting space twice
  // cout << m << endl;
  Creature creature1(4, 4);
  cout << "Path: " << creature1.solve(maze1) << endl;
  cout << maze1 << endl;
  Creature creature2(4, 4);
  cout << "Path: " << creature2.solve(maze2) << endl;
  cout << maze2 << endl;
  Creature creature3(4, 4);
  cout << "Path: " << creature3.solve(maze3) << endl;
  cout << maze3 << endl;
}
/**
 * @brief The method that runs the testing function and reports on if the test
 *  is successful
 *
 * @return int Returns 0 every time.
 */
int main() {
  test();
  cout << "Done!" << std::endl;
  return 0;
}