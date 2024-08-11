/**
 * @author Alexander Smith
 * @file creature.cpp
 * @brief This file contains the code that runs several operators related to
 *   solving mazes. These mazes are pregenerated and stored in text files. This
 *   class is reliant on the Maze class and uses it for the input for methods.
 */

#include "creature.h"
#include <string>

using namespace std;

/**
 * @brief function is the constructor for Creature. It sets the creatures
 * position in the maze using two inputs.
 *
 * @param Row The row in which the creature starts on
 * @param Col The column in which the creature starts on
 */
Creature::Creature(int Row, int Col) : row(Row), col(Col) {}

/**
 * @brief This funciton converts the column and row of a Creature into a string
 * which is returned.
 *
 * @param Out The ostream that contains the row and column of the creature.
 * @param Creature The creature with its information being converted into
 * a ostream
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &Out, const Creature &Creature) {
  Out << "Row:" << Creature.row << ", "
      << "Column:" << Creature.col << "\n";
  return Out;
}

/**
 * @brief This method compares the Creatures position to the mazes exit column
 * and exit row. If a creatures column position is the same as the exit column
 * and the creatures row position is the same as the exit row, then they are
 * at the exit.
 *
 * @param Maze A maze object generated with the maze class.
 * @return true If the creature is at the exit
 * @return false If the creature is not at the exit.
 */
bool Creature::atExit(const Maze &Maze) const {
  bool isAtExit = false;
  if (Maze.getExitColumn() == col && Maze.getExitRow() == row) {
    isAtExit = true;
  }
  return isAtExit;
}
/**
 * @brief This method solves the maze by using other methods within the class
 * and using the methods in the Maze class. It is capable of retracing its
 * steps and will mark places it has visited and places that are along
 * the path. This method impliments recursion, passing in the modified maze
 * class each step of the way.
 *
 * @param Maze A maze object generated with the Maze class. This maze object
 *  WILL be changed by the method.
 * @return string contianing the path through the maze the creature used to get
 * out.
 */
string Creature::solve(Maze &Maze) {
  string path;
  bool mazeSolved = false; // Tracks to see
  Maze.markAsPath(row, col);
  string result = "Null"; // Prevents default value from overlapping results.
  bool haveMoved = false; // Checks to see if we moved for use to if we need
                          // to backtrack later.

  result = goNorth(Maze);
  if (result != "X") {
    haveMoved = true;
  }
  movesAttempted[moveSlot] = 1;

  if (!haveMoved) {
    result = goEast(Maze);
    if (result != "X") {
      haveMoved = true;
    }
    movesAttempted[moveSlot] = 2;
  }
  if (!haveMoved) {
    result = goSouth(Maze);
    if (result != "X") {
      haveMoved = true;
    }
    movesAttempted[moveSlot] = 3;
  }
  if (!haveMoved) {
    result = goWest(Maze);
    if (result != "X") {
      haveMoved = true;
    }
    movesAttempted[moveSlot] = 4;
  }

  if (haveMoved) {
    moveList[moveSlot] = result;
    moveSlot++;
    if (atExit(Maze)) {
      mazeSolved = true;
    }
  } else { // Dead End
    bool suitableBacktrackFound = false;
    while (!suitableBacktrackFound) { // Handles backtracking
      if (moveList[moveSlot - 1] == "N") {
        goSouthBacktracking(Maze);
      } else if (moveList[moveSlot - 1] == "W") {
        goEastBacktracking(Maze);
      } else if (moveList[moveSlot - 1] == "E") {
        goWestBacktracking(Maze);
      } else {
        goNorthBacktracking(Maze);
      }
      moveList[moveSlot] = "";
      movesAttempted[moveSlot] = 0;
      moveSlot--;
      if (movesAttempted[moveSlot] < 4) {
        suitableBacktrackFound = true;
      }
    }
  }
  if (mazeSolved) {
    for (int i = 0; i < moveSlot; i++) { // Creates the string to be returned.
      path.append(moveList[i]);
    }
    delete[] movesAttempted;
    delete[] moveList;
  } else {
    path = solve(Maze); // Calls the function again
  }
  return path;
}

/**
 * @brief This method moves the creature north, marking its way as part of the
 * path. It will check to see if its about to move into a wall first so that
 * it doesn't phase through the wall as part of the solution.
 *
 * @param Maze  A maze object generated with the Maze class. This maze object
 *  WILL be changed by the method.
 * @return string Returns N if the move was successful and X if the way was
 *  blocked by a wall.
 */
string Creature::goNorth(Maze &Maze) {
  string resultOfMove;
  if (Maze.isClear(row - 1, col)) {
    row -= 1;
    resultOfMove = "N";
    Maze.markAsPath(row, col);
  } else {
    resultOfMove = "X";
  }
  return resultOfMove;
}
/**
 * @brief This method moves the creature west, marking its way as part of the
 * path. It will check to see if its about to move into a wall first so that
 * it doesn't phase through the wall as part of the solution.
 *
 * @param Maze A maze object generated with the Maze class. This maze object
 *  WILL be changed by the method.
 * @return string Returns W if the move was successful and X if the way was
 *  blocked by a wall.
 */
string Creature::goWest(Maze &Maze) {
  string resultOfMove;
  if (Maze.isClear(row, col - 1)) {
    col -= 1;
    resultOfMove = "W";
    Maze.markAsPath(row, col);
  } else {
    resultOfMove = "X";
  }
  return resultOfMove;
}
/**
 * @brief This method moves the creature east, marking its way as part of the
 * path. It will check to see if its about to move into a wall first so that
 * it doesn't phase through the wall as part of the solution.
 *
 * @param Maze A maze object generated with the Maze class. This maze object
 *  WILL be changed by the method.
 * @return string Returns E if the move was successful and X if the way was
 *  blocked by a wall.
 */
string Creature::goEast(Maze &Maze) {
  string resultOfMove;
  if (Maze.isClear(row, col + 1)) {
    col += 1;
    resultOfMove = "E";
    Maze.markAsPath(row, col);
  } else {
    resultOfMove = "X";
  }
  return resultOfMove;
}
/**
 * @brief This method moves the creature south, marking its way as part of the
 * path. It will check to see if its about to move into a wall first so that
 * it doesn't phase through the wall as part of the solution.
 *
 * @param Maze A maze object generated with the Maze class. This maze object
 *  WILL be changed by the method.
 * @return string Returns S if the move was successful and X if the way was
 *  blocked by a wall.
 */
string Creature::goSouth(Maze &Maze) {
  string resultOfMove;
  if (Maze.isClear(row + 1, col)) {
    row += 1;
    resultOfMove = "S";
    Maze.markAsPath(row, col);
  } else {
    resultOfMove = "X";
  }
  return resultOfMove;
}
/**
 * @brief This method brings the creature north during backtracking. It
 *  overides the places it passes over as merely being visited rather than
 *  being part of the  solution out of hte maze.
 *
 * @param Maze A maze object generated with the Maze class. This maze object
 *  WILL be changed by the method.
 */
void Creature::goNorthBacktracking(Maze &Maze) {
  Maze.markAsVisited(row, col);
  row -= 1;
}
/**
 * @brief This method brings the creature east during backtracking. It
 *  overides the places it passes over as merely being visited rather than
 *  being part of the  solution out of hte maze.
 *
 * @param Maze A maze object generated with the Maze class. This maze object
 *  WILL be changed by the method.
 */
void Creature::goEastBacktracking(Maze &Maze) {
  Maze.markAsVisited(row, col);
  col += 1;
}
/**
 * @brief This method brings the creature south during backtracking. It
 *  overides the places it passes over as merely being visited rather than
 *  being part of the  solution out of hte maze.
 *
 * @param Maze A maze object generated with the Maze class. This maze object
 *  WILL be changed by the method.
 */
void Creature::goSouthBacktracking(Maze &Maze) {
  Maze.markAsVisited(row, col);
  row += 1;
}
/**
 * @brief This method brings the creature west during backtracking. It
 *  overides the places it passes over as merely being visited rather than
 *  being part of the  solution out of hte maze.
 *
 * @param Maze A maze object generated with the Maze class. This maze object
 *  WILL be changed by the method.
 */
void Creature::goWestBacktracking(Maze &Maze) {
  Maze.markAsVisited(row, col);
  col -= 1;
}