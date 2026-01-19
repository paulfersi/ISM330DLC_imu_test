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

2. [WhoAmI](./whoami_test_imu.ino) test to check if:
    - the sensor is working on responding on the I²C bus at this address
    - it is actually the ISM330DLC
    - the communication is working

3. [Raw register test](./raw_register_test_imu.ino) (bypasses the library) 

Note: I tried with ``ISM330DLCSensor.h`` but it does not output any data

### Code overview

- The IMU (ISM330DLC) is connected via I²C at address 0x6A.
- Helper functions:
    - ``r8(reg)`` reads one byte from an IMU register.
    - ``r16(reg)`` reads two bytes and combines them into a signed 16-bit value.
    - ``w8(reg, val)`` writes one byte to a register.

#### Setup

- Initializes USB serial and I²C.
- Configures:
    - Accelerometer: ±4 g @ 104 Hz
    - Gyroscope: ±500 dps @ 104 Hz

> **NOTE**: These values are taken from the [ISM330DLC Datasheet](https://www.st.com/resource/en/datasheet/ism330dlc.pdf), specifically from the “Mechanical characteristics / Sensitivity” table.
> - **Accelerometer sensitivity** : For ±4 g, sensitivity = 0.122 mg/LSB -> 1000 / 0.122 ≈ 8192 LSB per g
> - **Gyroscope sentisivity** : For ±500 dps, sensitivity = 17.50 mdps/LSB -> 1000 / 17.5 ≈ 65.5 LSB per dps
>
> Where LSB stands for Least Significant Bit


#### Loop
- Reads raw accelerometer and gyroscope registers.
- Converts raw values to physical units:
    - Accelerometer: raw / 8192 → g
    - Gyroscope: raw / 65.5 → degrees/second
- Prints scaled values over serial at ~50 Hz.