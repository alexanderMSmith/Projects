//
// Created by Yusuf Pisan on 4/2/18.
// Modified by Alexander Smith on 4/22/21
// This file is the header file for timespan.cpp. It declares a list of methods
// and 3 variables but otherwise has no code. It also contains where the default
// values are set to 0.
//

#ifndef ASS2_TIMESPAN_H
#define ASS2_TIMESPAN_H

#include <iostream>

using namespace std;

class TimeSpan {
  friend ostream &operator<<(ostream &out, const TimeSpan &ts);

public:
  // explicit TimeSpan(int Hour = 0, int Minute = 0, int Second = 0);
  explicit TimeSpan(double hour = 0, double minute = 0, double second = 0);

  // add
  TimeSpan operator+(const TimeSpan &ts) const;

  // subtract
  TimeSpan operator-(const TimeSpan &ts) const;

  // check equality
  bool operator==(const TimeSpan &ts) const;

  // check if not equal
  bool operator!=(const TimeSpan &ts) const;

  // multiply timespan by an unsigned number
  TimeSpan operator*(unsigned int number) const;

  // Add and assign.
  TimeSpan operator+=(const TimeSpan &ts) const;
  // Subtract and assign
  TimeSpan operator-=(const TimeSpan &ts) const;
  // Check if greater than
  bool operator>(const TimeSpan &ts) const;
  // Check if less than
  bool operator<(const TimeSpan &ts) const;
  // Check if greater than or equal too
  bool operator>=(const TimeSpan &ts) const;
  // Check if less than or equal too
  bool operator<=(const TimeSpan &ts) const;

  // hour component of timespan
  double getHour() const;

  // minute component of timespan
  double getMinute() const;

  // second component of timespan
  double getSecond() const;

  // true if timespan is 0 or larger
  bool isPositive() const;

private:
  double seconds;
  double minutes;
  double hours;
};

#endif // ASS2_TIMESPAN_H