#include <Wire.h>
#define IMU_ADDR 0x6A

uint8_t r8(uint8_t reg) {
  Wire.beginTransmission(IMU_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(IMU_ADDR, (uint8_t)1);
  return Wire.read();
}

int16_t r16(uint8_t regL) {
  uint8_t lo = r8(regL);
  uint8_t hi = r8(regL + 1);
  return (int16_t)((hi << 8) | lo);
}

void w8(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(IMU_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  Wire.begin();

  // Accel: 104 Hz, ±4g
  w8(0x10, 0x48);
  // Gyro: 104 Hz, ±500 dps
  w8(0x11, 0x48);

  Serial.println("ax,ay,az,gx,gy,gz");
}

void loop() {
  int16_t gx = r16(0x22);
  int16_t gy = r16(0x24);
  int16_t gz = r16(0x26);
  int16_t ax = r16(0x28);
  int16_t ay = r16(0x2A);
  int16_t az = r16(0x2C);


  Serial.print(ax); Serial.print(',');
  Serial.print(ay); Serial.print(',');
  Serial.print(az); Serial.print(',');
  Serial.print(gx); Serial.print(',');
  Serial.print(gy); Serial.print(',');
  Serial.println(gz);

  delay(20); // ~50 Hz
}
