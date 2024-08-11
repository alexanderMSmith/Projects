
#include <cassert>
#include <iostream>

#include "BinaryTree.h"

using namespace std;

/**
 * @brief A test method to remove even values from a tree.
 *
 * @param threadedCopy The tree to have its evens removed.
 */
void removeEvens(BinaryTree &threadedCopy) {
  int i = 2;
  while (threadedCopy.remove(i)) {
    i += 2;
  }
}

/**
 * @brief A test method that takes in values from the user.
 *
 * @return int The values the user inputs.
 */
int input() {
  int n;
  string prompt = "0 to end ";
  cout << prompt;
  cin >> n;
  while (n < 0) {
    cout << prompt;
    cin >> n;
  }
  return n;
}

/**
 * @brief The main testing method for the BinaryTree, BinaryNode, and Iterator
 * classes.
 *
 */
void Test() {

  int n = input();
  while (n > 0) {
    BinaryTree temp(n);

    BinaryTree tempCopy(temp);

    cout << endl << "original BinaryTree = " << n << endl;
    cout << temp;

    cout << tempCopy;
    removeEvens(tempCopy);

    cout << tempCopy;

    cout << temp;

    n = input();
  }
}

/**
 * @brief The main function that calls the main test method.
 *
 * @return int 0
 */
int main() {
  Test();

  return 0;
}
