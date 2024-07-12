#include "lcd.h"

LCD::LCD(int rs, int rw, int e, int d4, int d5, int d6, int d7) : RS(rs), RW(rw), E(e), D4(d4), D5(d5), D6(d6), D7(d7) {}

void LCD::init() {
  // Set pin modes
  pinMode(RS, OUTPUT);
  pinMode(RW, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  // Initialization sequence
  lcdCommand(0x33);
  lcdCommand(0x32);
  lcdCommand(0x28);
  lcdCommand(0x0C);
  lcdCommand(0x01);
  delay(2);
}

void LCD::lcdCommand(unsigned char command) {
  digitalWrite(RS, LOW);
  send(command);
}

void LCD::lcdData(unsigned char data) {
  digitalWrite(RS, HIGH);
  send(data);
}

void LCD::send(unsigned char value) {
  digitalWrite(D4, (value >> 4) & 0x01);
  digitalWrite(D5, (value >> 5) & 0x01);
  digitalWrite(D6, (value >> 6) & 0x01);
  digitalWrite(D7, (value >> 7) & 0x01);

  pulseEnable();

  digitalWrite(D4, value & 0x01);
  digitalWrite(D5, (value >> 1) & 0x01);
  digitalWrite(D6, (value >> 2) & 0x01);
  digitalWrite(D7, (value >> 3) & 0x01);

  pulseEnable();
}

void LCD::pulseEnable() {
  digitalWrite(E, LOW);
  delayMicroseconds(1);
  digitalWrite(E, HIGH);
  delayMicroseconds(1);
  digitalWrite(E, LOW);
  delayMicroseconds(100);
}

void LCD::clear() {
  lcdCommand(0x01);
  delay(2);
}

void LCD::setCursor(int col, int row) {
  int row_offsets[] = {0x00, 0x40, 0x14, 0x54};
  lcdCommand(0x80 | (col + row_offsets[row]));
}

void LCD::lcdPrint(String str) {
  for (int i = 0; i < str.length(); i++) {
    lcdData(str[i]);
  }
}
