/**
 * @file Table.cpp
 * @author Alexander Smith
 * @brief This class generates a truth table with the inputted amount of
 * propositions.
 * @version 0.1
 * @date 2021-05-20
 *
 */
#include <iostream>
#include <string>
using namespace std;
/**
 * @brief This is the recursive function that generates a truth table
 * of the given propositional amounts.
 *
 * @param n The number of propositions left to compute.
 * @param sofar The value that retains the recursive truth table data that
 * the fucntion generates and assigns.
 */
void truthTableR(int n, const std::string &sofar = "") {
  if (n <= 1) {
    std::cout << sofar << "T" << std::endl;
    std::cout << sofar << "F" << std::endl;
  } else {
    truthTableR(n - 1, sofar + "T");
    truthTableR(n - 1, sofar + "F");
  }
}

/**
 * @brief This is the driver method for Table.cpp. This is where the original
 * table is generated, but is not where it is printed. It is printed in
 * truthTableR.
 *
 * @return int Always returns 0.
 */
int main() {
  int numProps;
  std::cout << "How many propositions?";
  std::cin >> numProps;
  std::string table;
  truthTableR(numProps, table);
  return 0;
}