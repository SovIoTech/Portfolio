#include <Arduino.h>
#include "lcd.h"
#include "rtc.h"


// LCD pins
const int RS = 8;
const int RW = 9;
const int E = 10;
const int D4 = 11;
const int D5 = 12;
const int D6 = 13;
const int D7 = 14;

LCD lcd(RS, RW, E, D4, D5, D6, D7);
DS1307_HAL rtc;

void setup() {
  Serial.begin(9600);

  rtc.begin();
  lcd.init();

  // Set the initial time (adjust as needed)
  rtc.initializeTime(2024, 3, 4, 12, 0, 0);
}

void loop() {
  int year, month, day, hour, minute, second;

  rtc.readTime(year, month, day, hour, minute, second);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.lcdPrint("Current time:");
  lcd.setCursor(0, 1);
  lcd.lcdPrint(String(year) + "-" + String(month) + "-" + String(day) + " " + String(hour) + ":" + String(minute) + ":" + String(second));

  delay(1000);
}
