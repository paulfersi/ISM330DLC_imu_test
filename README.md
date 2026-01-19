# Tests for ISM330DLC IMU

Tests were performed on Arduino MKR WiFi 1010

### PINOUT

| Arduino    | IMU board |
| -------- | ------- |
| VCC  | VDD   |
| VCC | VDDIO     |
| GND    | GND    |
| SDA | SDA |
| SCL | SCL |
| VCC | CS |
| GND | SD0 |

### Tests to perform

1. ensure that we are using 3.3V (Not 5V)

2. WhoAmI test to check if:
    - the sensor is working on responding on the I²C bus at this address
    - it is actually the ISM330DLC
    - the communication is working

3. Raw register test (bypasses the library) 

Note: I tried with ``ISM330DLCSensor.h`` but it does not output any data