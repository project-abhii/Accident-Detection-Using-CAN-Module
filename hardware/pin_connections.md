# Hardware Pin Connections

The following pin configuration is taken from the project report.

| Component | Pin | Arduino Pin |
|---|---|---|
| Ultrasonic Sensor | VCC | 5V |
| Ultrasonic Sensor | GND | GND |
| Ultrasonic Sensor | TRIG | D8 |
| Ultrasonic Sensor | ECHO | D9 |
| Potentiometer | VCC | 5V |
| Potentiometer | GND | GND |
| Potentiometer | SIGNAL | A0 |
| CAN Module | CS | D10 |
| CAN Module | SCK | D13 |
| CAN Module | SI | D11 |
| CAN Module | SO | D12 |
| LCD I2C | SDA | A4 |
| LCD I2C | SCL | A5 |
| GSM Module | TX | D3 |
| GSM Module | RX | D4 |
| Buzzer | +VE | D6 |
| Buzzer | -VE | GND |

## Important Note

The project's hardware connection table specifies:

- TRIG → D8
- ECHO → D9

However, the transmitter source code in the project report defines:

- TRIG → D9
- ECHO → D8

Therefore, the final physical connections should be verified with the actual prototype before using the code.
