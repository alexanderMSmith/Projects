/*
// Created by Yusuf Pisan on 4/2/18.
// Modified by Alexander Smith on 4/21/18
// This file is the main file containing the code for the TimeSpan class. This
file has  operators
// such as o >,<,<=,>=, *, +,-, and <<. Additionally, this file has 3 getter
methods that will get the
// hour, minute, and second count for the class.
// The class is able to dynamically carry over values from a excess of seconds
or minutes and increase the
// count of the next higher variable as needed.
//
*/

#include "timespan.h"
#include <cmath>
using namespace std;

// This method prints out the information of the class in a format. It responds
// based on if the time is negatively aligned or positively. Pre Condition: A
// TimeSpan is being printed. Post Condition: The time is printed out in a
// "X:XX:XX" format.
ostream &operator<<(ostream &out, const TimeSpan &ts) {
  bool printPositive = ts.isPositive();
  if (printPositive) {
    if (ts.minutes > 9 && ts.seconds > 9) {
      out << ts.hours << ':' << ts.minutes << ':' << ts.seconds;
    } else if (ts.minutes < 10 && ts.seconds > 9) {
      out << ts.hours << ':' << 0 << ts.minutes << ':' << ts.seconds;
    } else if (ts.minutes > 9 && ts.seconds < 10) {
      out << ts.hours << ':' << ts.minutes << ':' << 0 << ts.seconds;
    } else if (ts.minutes < 10 && ts.seconds < 10) {
      out << ts.hours << ':' << 0 << ts.minutes << ':' << 0 << ts.seconds;
    }

  } else {
    double secondValue = abs(ts.seconds);
    double minuteValue = abs(ts.minutes);
    double hourValue = abs(ts.hours);
    if (secondValue > 9 && minuteValue > 9) {
      out << '-' << hourValue << ':' << minuteValue << ':' << secondValue;
    } else if (minuteValue < 10 && secondValue > 9) {
      out << '-' << hourValue << ':' << 0 << minuteValue << ':' << secondValue;
    } else if (minuteValue > 9 && secondValue < 10) {
      out << '-' << hourValue << ':' << minuteValue << ':' << 0 << secondValue;
    } else if (minuteValue < 10 && secondValue < 10) {
      out << '-' << hourValue << ':' << 0 << minuteValue << ':' << 0
          << secondValue;
    }
  }
  return out;
}

/* This is the consturctor for Time Span. It takes in an hour, minute, and
second count.
// If it gets none of these, it will set them all equal to 0.
// It goes through the values passed in and makes sure they are all converted to
proper clock times.
// It will aslo properly assign negative values if they are passed in.
// Pre-Condition: An hour, minute, and second is passed in or it is called by
itself.
//Post-Condition: A TimeSpan is made with an hour, minute, and second count.
*/
TimeSpan::TimeSpan(double hour, double minute, double second) {
  double mainNumber;
  double remainder = modf(hour, &mainNumber);
  if (remainder != 0) {
    remainder = remainder * 60;
    minute = remainder + minute;
    hour = mainNumber;
  }
  mainNumber = 0;
  remainder = modf(minute, &mainNumber);
  if (remainder != 0) {
    remainder = remainder * 60;
    second = remainder + second;
    minute = mainNumber;
  }
  mainNumber = 0;
  remainder = modf(second, &mainNumber); // NOLINT
  remainder = 0;
  second = mainNumber + remainder;
  bool balanced = false;
  double carryOver = 0;
  double checkValue = second;
  while (!balanced) {
    if (checkValue >= 60) {
      carryOver++;
      checkValue = checkValue - 60;

    } else if (checkValue >= 0) {
      balanced = true;
    } else {
      carryOver--;
      checkValue = checkValue + 60;
    }
  }
  seconds = checkValue;
  minutes = minute + carryOver;
  carryOver = 0;
  balanced = false;
  while (!balanced) {
    if (minutes >= 60) {
      carryOver++;
      minutes = minutes - 60;
    } else if (minutes >= 0) {
      balanced = true;
    } else {
      carryOver--;
      minutes = minutes + 60;
    }
  }
  hours = hour + carryOver;
}

// returns the hour components.
// Pre-condiiton: The object exists and has an hours value assigned
// Post Condition: The hour value is returned
double TimeSpan::getHour() const { return hours; }

// returns the minute components.
// Pre-condiiton: The object exists and has an minute value assigned
// Post Condition: The minute value is returned
double TimeSpan::getMinute() const { return minutes; }

// returns the second components.
// Pre-condiiton: The object exists and has an second value assigned
// Post Condition: The second value is returned
double TimeSpan::getSecond() const { return seconds; }

/*
// This function checks to see if TimeSpan is positive. If it is positive, it
will return true. If not, it will return false.
//Pre Condition: The object exists and variables are assigned.
// Post Condition: Returns true if all the values are positive, false if they
are not all postive.
*/
bool TimeSpan::isPositive() const {
  bool isNotNegative = (hours >= 0 && minutes >= 0 && seconds >= 0);
  return isNotNegative;
}

/*
This function adds the current TimeSPan with a second one that is passed in,
returning the sum.

Pre condition: two Timespans exist and one is passed in.
Post condition: The first item. is made equal to the sum.
*/
TimeSpan TimeSpan::operator+(const TimeSpan &ts) const {
  TimeSpan tsSum;
  bool balanced = false;
  double carryOver = 0;
  tsSum.seconds = ts.seconds + seconds;
  while (!balanced) {
    if (tsSum.seconds >= 60) {
      carryOver++;
      tsSum.seconds = tsSum.seconds - 60;
    } else {
      balanced = true;
    }
  }
  tsSum.minutes = ts.minutes + minutes + carryOver;
  balanced = false;
  carryOver = 0;
  while (!balanced) {
    if (tsSum.minutes >= 60) {
      carryOver++;
      tsSum.minutes = tsSum.minutes - 60;
    } else {
      balanced = true;
    }
  }
  tsSum.hours = ts.hours + hours + carryOver;
  return tsSum;
}

/*
//This function subtracts the current TimeSpan with a second one that is passed
in, returning the sum.

//Pre condition: two Timespans exist and one is passed in.
//Post condition: The first item. is made equal to the result.
*/
TimeSpan TimeSpan::operator-(const TimeSpan &ts) const {
  TimeSpan tsSub;
  bool balanced = false;
  double carryOver = 0;
  tsSub.seconds = seconds - ts.seconds;
  while (!balanced && hours > 0) {
    if (tsSub.seconds < 0) {
      carryOver++;
      tsSub.seconds = tsSub.seconds + 60;
    } else {
      balanced = true;
    }
  }
  tsSub.minutes = minutes - ts.minutes - carryOver;
  balanced = false;
  carryOver = 0;
  while (!balanced && hours > 0) {
    if (tsSub.minutes < 0) {
      carryOver++;
      tsSub.minutes = tsSub.minutes + 60;
    } else {
      balanced = true;
    }
  }
  tsSub.hours = hours - ts.hours - carryOver;
  return tsSub;
}

/*
//This method takes in an integer value and multiplies each of the clocks values
with the integer.
//It starts with the seconds, and throughout thep rocess, makes sure to carry
over the overflow without multiplying
//the overflow erroniously.
//Pre condition: A TimeSpan is being mulitplied by an integer.
//Post-Condition: The old TimeSpan values is replaced by the product of the old
values with the integer.
*/
TimeSpan TimeSpan::operator*(unsigned int number) const {
  TimeSpan tsLarge;
  double carryOver = 0;
  bool balanced = false;
  tsLarge.seconds = seconds * number;
  while (!balanced) {
    if (tsLarge.seconds >= 60) {
      carryOver++;
      tsLarge.seconds = tsLarge.seconds - 60;
    } else {
      balanced = true;
    }
  }
  tsLarge.minutes = (minutes * number) + carryOver;
  balanced = false;
  carryOver = 0;
  while (!balanced) {
    if (tsLarge.minutes >= 60) {
      carryOver++;
      tsLarge.minutes = tsLarge.minutes - 60;
    } else {
      balanced = true;
    }
  }
  tsLarge.hours = (hours * number) + carryOver;
  return tsLarge;
}

/*
//This function comapares two TimeSpans. If the hour, minute, and second count
are all equal, it returns true.
//Pre Condition: Two Timespans that have been assigned values are being
compares.
//Post Condition: If the hours, minutes, and seconds count are all equal, it
returns true. Otherwise it returns false.
*/
bool TimeSpan::operator==(const TimeSpan &ts) const {
  bool returnValue = true;
  if (hours != ts.hours) {
    returnValue = false;
  } else if (minutes != ts.minutes) {
    returnValue = false;
  } else if (seconds != ts.seconds) {
    returnValue = false;
  }

  return returnValue;
}

/*
//This function comapares two TimeSpans. If the hour, minute, and second count
are all equal, it returns false.
//Pre Condition: Two Timespans that have been assigned values are being
compares.
//Post Condition: If the hours, minutes, and seconds count are all equal, it
returns false. Otherwise it returns true.
*/
bool TimeSpan::operator!=(const TimeSpan &ts) const {
  bool returnValue = false;
  if (hours != ts.hours) {
    returnValue = true;
  }
  if (minutes != ts.minutes) {
    returnValue = true;
  }
  if (seconds != ts.seconds) {
    returnValue = true;
  }

  return returnValue;
}
/*
This function checks if the first Timespan Object is less than  to
Timespan Object. It returns a bool value. If the first object is less than  to
the Timespan Object, it returns true. Otherwise, it returns false.

Pre-condition: Two Timespan objects exist.
Post Condition: True or false is returned.

*/
bool TimeSpan::operator>(const TimeSpan &ts) const {
  bool returnValue = false;
  if (hours > ts.hours) {
    returnValue = true;
  } else if (hours < ts.hours) {
    returnValue = false;
  } else if (minutes > ts.minutes) {
    returnValue = true;
  } else if (minutes < ts.minutes) {
    returnValue = false;
  } else if (seconds > ts.seconds) {
    returnValue = true;
  } else if (seconds < ts.seconds) {
    returnValue = false;
  }

  return returnValue;
}
/*
This function checks if the first Timespan Object is more than  to
Timespan Object. It returns a bool value. If the first object is more than  to
the Timespan Object, it returns true. Otherwise, it returns false.

Pre-condition: Two Timespan objects exist.
Post Condition: True or false is returned.

*/

bool TimeSpan::operator<(const TimeSpan &ts) const {
  bool returnValue = false;
  if (hours > ts.hours) {
    returnValue = false;
  } else if (hours < ts.hours) {
    returnValue = true;
  } else if (minutes > ts.minutes) {
    returnValue = false;
  } else if (minutes < ts.minutes) {
    returnValue = true;
  } else if (seconds > ts.seconds) {
    returnValue = false;
  } else if (seconds < ts.seconds) {
    returnValue = true;
  }

  return returnValue;
}
/*
This function checks if the first Timespan Object is less than or equal to
Timespan Object. It returns a bool value. If the first object is less than or
equal to the Timespan Object, it returns true. Otherwise, it returns false.

Pre-condition: Two Timespan objects exist.
Post Condition: True or false is returned.

*/
bool TimeSpan::operator<=(const TimeSpan &ts) const {
  bool returnValue = true;
  if (hours == ts.hours && minutes == ts.minutes && seconds == ts.seconds) {
    returnValue = true;
  } else if (hours > ts.hours) {
    returnValue = false;
  } else if (hours < ts.hours) {
    returnValue = true;
  } else if (minutes > ts.minutes) {
    returnValue = false;
  } else if (minutes < ts.minutes) {
    returnValue = true;
  } else if (seconds > ts.seconds) {
    returnValue = false;
  } else if (seconds < ts.seconds) {
    returnValue = true;
  }

  return returnValue;
}
/*
This function checks if the first Timespan Object is more than or equal to
Timespan Object. It returns a bool value. If the first object is more than or
equal to the Timespan Object, it returns true. Otherwise, it returns false.

Pre-condition: Two Timespan objects exist.
Post Condition: True or false is returned.

*/
bool TimeSpan::operator>=(const TimeSpan &ts) const {
  bool returnValue = false;
  if (hours == ts.hours && minutes == ts.minutes && seconds == ts.seconds) {
    returnValue = true;
  } else if (hours > ts.hours) {
    returnValue = true;
  } else if (hours < ts.hours) {
    returnValue = false;
  } else if (minutes > ts.minutes) {
    returnValue = true;
  } else if (minutes < ts.minutes) {
    returnValue = false;
  } else if (seconds > ts.seconds) {
    returnValue = true;
  } else if (seconds < ts.seconds) {
    returnValue = false;
  }

  return returnValue;
}
/*
This function has a simiillar use to the addition function. However, it instead
uses the += operator.

Pre condition: two Timespans exist and one is passed in.
Post condition: The first item. is made equal to the sum.
*/
TimeSpan TimeSpan::operator+=(const TimeSpan &ts) const {
  TimeSpan tsSum;
  bool balanced = false;
  double carryOver = 0;
  tsSum.seconds = ts.seconds + seconds;
  while (!balanced) {
    if (tsSum.seconds >= 60) {
      carryOver++;
      tsSum.seconds = tsSum.seconds - 60;
    } else {
      balanced = true;
    }
  }
  tsSum.minutes = ts.minutes + minutes + carryOver;
  balanced = false;
  carryOver = 0;
  while (!balanced) {
    if (tsSum.minutes >= 60) {
      carryOver++;
      tsSum.minutes = tsSum.minutes - 60;
    } else {
      balanced = true;
    }
  }
  tsSum.hours = ts.hours + hours + carryOver;
  return tsSum;
}

/*
This function has a simiillar use to the subtraction function. However, it
instead uses the -= operator.

Pre condition: two Timespans exist and one is passed in.
Post condition: The first item. is made equal to the result.
*/
TimeSpan TimeSpan::operator-=(const TimeSpan &ts) const {
  TimeSpan tsSub;
  bool balanced = false;
  double carryOver = 0;
  tsSub.seconds = seconds - ts.seconds;
  while (!balanced && hours > 0) {
    if (tsSub.seconds < 0) {
      carryOver++;
      tsSub.seconds = tsSub.seconds + 60;
    } else {
      balanced = true;
    }
  }
  tsSub.minutes = minutes - ts.minutes - carryOver;
  balanced = false;
  carryOver = 0;
  while (!balanced && hours > 0) {
    if (tsSub.minutes < 0) {
      carryOver++;
      tsSub.minutes = tsSub.minutes + 60;
    } else {
      balanced = true;
    }
  }
  tsSub.hours = hours - ts.hours - carryOver;
  return tsSub;
}