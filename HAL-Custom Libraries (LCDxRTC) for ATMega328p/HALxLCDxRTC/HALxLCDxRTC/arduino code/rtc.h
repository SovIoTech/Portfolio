#include <Arduino.h>

#ifndef DS1307_HAL_H
#define DS1307_HAL_H

class DS1307_HAL {
public:
  DS1307_HAL();
  void begin();
  void initializeTime(int year, int month, int day, int hour, int minute, int second);
  void readTime(int& year, int& month, int& day, int& hour, int& minute, int& second);

private:
  int decToBcd(int val);
  int bcdToDec(int bcd);
};

#endif
