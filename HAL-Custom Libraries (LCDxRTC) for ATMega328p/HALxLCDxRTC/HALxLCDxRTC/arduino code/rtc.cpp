#include "rtc.h"
#include <Wire.h>

#define DS1307_ADDRESS 0x68 // I2C address for DS1307

DS1307_HAL::DS1307_HAL() {}

void DS1307_HAL::begin() {
  Wire.begin();
}

void DS1307_HAL::initializeTime(int year, int month, int day, int hour, int minute, int second) {
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x00); // Start at register 0 (seconds)
  Wire.write(decToBcd(second) & 0x7F); // Mask the 7th bit to handle the CH (Clock Halt) bit
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour) & 0x3F); // Mask the 7th and 8th bits for 24-hour mode
  Wire.write(decToBcd(day));
  Wire.write(decToBcd(day));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year - 2000));
  Wire.endTransmission();
}

void DS1307_HAL::readTime(int& year, int& month, int& day, int& hour, int& minute, int& second) {
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x00); // Start at register 0 (seconds)
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7); // Request 7 bytes (seconds, minutes, hours, day, date, month, year)

  second = bcdToDec(Wire.read() & 0x7F); // Mask the 7th bit to handle the CH (Clock Halt) bit
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read() & 0x3F); // Mask the 7th and 8th bits for 24-hour mode
  day = bcdToDec(Wire.read());
  // Note: Date is read twice, you may want to fix this in your code
  day = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = 2000 + bcdToDec(Wire.read());
}

int DS1307_HAL::decToBcd(int val) {
  return ((val / 10) << 4) + (val % 10);
}

int DS1307_HAL::bcdToDec(int bcd) {
  return ((bcd / 16) * 10) + (bcd % 16);
}
