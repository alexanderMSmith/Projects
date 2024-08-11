//
// Created by Yusuf Pisan on 4/2/18.
// Modified by Alexander Smith on 4/22/21
// This file is the driver function for the TimeSpan class. It tests every line
// of code in timespan.cpp and ensures that everything is in working order.
//
#include <cassert>
#include <iostream>
#include <sstream>

#include "timespan.h"

using namespace std;

// testing constructor
void test1() {
  TimeSpan ts(1, 20, 30);
  stringstream ss;
  ss << ts;
  assert(ss.str() == "1:20:30");
  TimeSpan ts2(4, -20, -90);
  ss.str("");
  ss << ts2;

  assert(ss.str() == "3:38:30");

  TimeSpan ts3(1.5, 30.5, -90);
  ss.str("");
  ss << ts3;
  assert(ss.str() == "1:59:00");

  TimeSpan ts4(0, 0.07, 0);
  ss.str("");
  ss << ts4;
  assert(ss.str() == "0:00:04");
  cout << "test1 complete" << endl;
}

// testing equality, addition, subtraction, multiplication
void test2() {
  TimeSpan ts(1, 20, 30);
  TimeSpan ts2(1, 20, 30);
  TimeSpan ts3(0, 0, 0);
  assert(ts == ts2);
  assert(!(ts != ts2));
  assert(ts != ts3);
  assert((ts + ts + ts) == (ts2 * 3));
  assert((ts * 5) == (ts2 * 4) + ts2);
  assert((ts * 5) == (ts2 * 6) - ts2);
  assert((ts + ts - ts) == ((ts2 * 2) - ts));
  assert((ts - ts2) == ts3);
  assert((ts3 * 5) == ts3);
  cout << "test2 complete" << endl;
}

// Testing handling negatives
void test3() {
  TimeSpan ts0(0, 0, 0);
  TimeSpan ts1(0, 0, 10);
  TimeSpan ts2 = ts0 - ts1;
  assert(ts1.isPositive() && !ts2.isPositive());
  stringstream ss;
  ss << ts2;
  assert(ss.str() == "-0:00:10");
  cout << "test3 complete" << endl;
}
// Tests += and -= to make sure they are equivelent to + and -. These are the
// same so we only need t ocompleatly cover 1.
void test4() {
  TimeSpan ts0(2, 5, 9);
  TimeSpan ts(1, 20, 30);
  TimeSpan ts2(1, 20, 30);
  TimeSpan ts3(0, 0, 0);
  TimeSpan ts5(0, 0, 0);
  TimeSpan ts6(0, 0, 10);
  TimeSpan ts7 = ts5 -= ts6;
  TimeSpan ts8 = ts2 -= ts * 2;
  TimeSpan ts9 = ts0 -= ts6;
  assert((ts0 += ts0) == (ts0 + ts0));   // NOLINT
  assert((ts0 -= ts0) == (ts0 - ts0));   // NOLINT
  assert((ts += ts += ts) == (ts2 * 3)); // NOLINT
  assert((ts -= ts2) == ts3);            // NOLINT
  stringstream ss;
  ss.str("");
  ss << ts7;
  assert(ss.str() == "-0:00:10");
  ss.str("");
  ss << ts8;
  assert(ss.str() == "-2:39:30");
  ss.str("");
  ss << ts9;
  assert(ss.str() == "2:04:59");
  cout << "test4 complete" << endl;
}
// Tests >=, >, <, <=
void test5() {
  TimeSpan ts0(1, 2, 4);
  TimeSpan ts1(2, 4, 6);
  TimeSpan ts2(2, 4, 6);
  TimeSpan ts3(2, 5, 7);
  TimeSpan ts4(2, 4, 7);
  TimeSpan ts5(2, 4, 8);
  assert(ts0 < ts1);
  assert(ts0 <= ts1);
  assert(ts1 > ts0);
  assert(ts1 >= ts0);
  assert(ts2 >= ts1);
  assert(!(ts2 > ts1));
  assert(ts2 <= ts1);
  assert(!(ts2 < ts1));
  assert(!(ts0 > ts1));
  assert(!(ts0 >= ts1));
  assert(!(ts1 < ts0));
  assert(!(ts1 <= ts0));
  assert(ts3 > ts2);
  assert(ts3 >= ts2);
  assert(ts4 > ts2);
  assert(ts4 >= ts2);
  assert(ts2 < ts3);
  assert(ts2 <= ts3);
  assert(ts2 < ts4);
  assert(ts2 <= ts4);
  assert(ts4 > ts2);
  assert(ts4 >= ts2);
  assert(!(ts4 > ts3));
  assert(!(ts4 >= ts3));
  assert(!(ts4 > ts5));
  assert(!(ts4 >= ts5));
  assert(!(ts3 < ts4));
  assert(!(ts3 <= ts4));
  assert(!(ts5 < ts4));
  assert(!(ts5 <= ts4));
  cout << "test5 complete" << endl;
}
// Tests the get methods
void test6() {
  TimeSpan ts0(1, 2, 4);
  bool passTest = ts0.getHour() == 1;
  assert(passTest);
  passTest = ts0.getMinute() == 2;
  assert(passTest);
  passTest = ts0.getSecond() == 4;
  assert(passTest);
  cout << "test6 complete" << endl;
}
// Closes off ==
void test7() {
  TimeSpan ts0(1, 2, 3);
  TimeSpan ts1(1, 2, 4);
  TimeSpan ts2(1, 3, 4);
  TimeSpan ts3(0, 2, 3);
  assert(!(ts0 == ts1));
  assert(!(ts1 == ts2));
  assert(!(ts0 == ts2));
  assert(!(ts3 == ts0));
  cout << "test7 complete" << endl;
}

// Closes off the constructor
void test8() {
  TimeSpan ts0(-4, -5, -7);
  stringstream ss;
  ss.str("");
  ss << ts0;
  assert(ss.str() == "-5:54:53");
  TimeSpan ts1(0, 0, 90);
  ss.str("");
  ss << ts1;
  assert(ss.str() == "0:01:30");
  TimeSpan ts2(0, 90, 0);
  ss.str("");
  ss << ts2;
  assert(ss.str() == "1:30:00");
  cout << "test8 complete" << endl;
}
// Closes off the printer.
void test9() {
  TimeSpan ts0(-4, -11, -51);
  stringstream ss;
  ss.str("");
  ss << ts0;
  assert(ss.str() == "-5:48:09");
  TimeSpan ts1(-4, -51, -51);
  ss.str("");
  ss << ts1;
  assert(ss.str() == "-5:08:09");
  cout << "test9 complete" << endl;
}

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  cout << "Done." << std::endl;
  return 0;
}