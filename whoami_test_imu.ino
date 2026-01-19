#include <Wire.h>

/*
It should return
 Found 0x60 WHO_AM_I=0x04
 Found 0x6A WHO_AM_I=0x6A -> this is for data
 Found 0x6B WHO_AM_I=0xFF
*/

byte readReg(byte addr, byte reg) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  byte e1 = Wire.endTransmission(false);
  if (e1 != 0) return 0xFF;

  byte n = Wire.requestFrom((int)addr, 1, (int)true);
  if (n != 1) return 0xFF;
  return Wire.read();
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  Wire.begin();
  Wire.setClock(50000);

  Serial.println("Scan + WHO_AM_I");

  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found 0x");
      if (addr < 16) Serial.print("0");
      Serial.print(addr, HEX);

      byte who = readReg(addr, 0x0F);
      Serial.print("  WHO_AM_I=0x");
      if (who < 16) Serial.print("0");
      Serial.println(who, HEX);
    }
  }
}

void loop() {}
