#include <Arduino.h>

#ifndef LCD_H
#define LCD_H

class LCD {
public:
  LCD(int rs, int rw, int e, int d4, int d5, int d6, int d7);
  void init();
  void lcdCommand(unsigned char command);
  void lcdData(unsigned char data);
  void clear();
  void setCursor(int col, int row);
  void lcdPrint(String str);

private:
  int RS;
  int RW;
  int E;
  int D4;
  int D5;
  int D6;
  int D7;

  void send(unsigned char value);
  void pulseEnable();
};

#endif
