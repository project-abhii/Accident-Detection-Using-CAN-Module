# 🚗 Arduino-Based Collision Detection Warning System Using CAN Protocol and SMS Alert

An embedded automotive-safety prototype that measures obstacle distance and speed, transfers data between two Arduino units using CAN communication, provides a collision warning, controls a DC motor, and sends an SMS alert through GSM when the programmed speed threshold is exceeded.

## Features

- Ultrasonic-based obstacle distance measurement
- Speed sensing
- CAN-based communication between transmitter and receiver
- 16×2 I2C LCD monitoring
- Buzzer-based collision warning
- DC motor control
- GSM-based SMS alert
- Arduino Uno R3 controller on transmitter and receiver sides

## System Architecture

```text
TRANSMITTER UNIT                         RECEIVER UNIT

Ultrasonic Sensor ─┐
                    ├─> Arduino UNO ─> CAN ─> Arduino UNO ─┬─> LCD
Speed Sensor ───────┘                                      ├─> Buzzer
                                                          ├─> DC Motor
                                                          └─> GSM ─> SMS
```

## Working Principle

1. The transmitter Arduino measures obstacle distance using the ultrasonic sensor.
2. Vehicle/motor speed is measured using the speed sensor.
3. Distance and speed are packed into a CAN message.
4. The CAN bus transfers the data to the receiver Arduino.
5. The receiver displays the received values on the LCD.
6. When distance falls below the programmed collision threshold, the buzzer is activated and the motor is stopped.
7. When the programmed speed threshold is exceeded, the GSM module sends an SMS alert.
8. The process repeats continuously.

## Hardware

### Transmitter

- Arduino Uno R3
- Ultrasonic distance sensor
- Speed sensor
- CAN module
- 16×2 I2C LCD
- Potentiometer
- Power supply

### Receiver

- Arduino Uno R3
- CAN module
- GSM module
- 16×2 I2C LCD
- Buzzer
- DC motor
- Power supply

## Important Thresholds in the Reported Implementation

- Collision condition: `distance < 20 cm`
- SMS condition: `motorSpeed > 200`
- CAN bitrate: `500 kbps`

These values are taken from the project report/code and are prototype thresholds, not automotive safety standards.

## Pin Connections

| Component | Pin | Arduino Pin |
|---|---|---|
| Ultrasonic sensor | VCC | 5V |
| Ultrasonic sensor | GND | GND |
| Ultrasonic sensor | TRIG | D8 |
| Ultrasonic sensor | ECHO | D9 |
| Potentiometer | VCC | 5V |
| Potentiometer | GND | GND |
| Potentiometer | SIGNAL | A0 |
| CAN module | CS | D10 |
| CAN module | SCK | D13 |
| CAN module | SI | D11 |
| CAN module | SO | D12 |
| LCD I2C | SDA | A4 |
| LCD I2C | SCL | A5 |
| GSM module | TX | D3 |
| GSM module | RX | D4 |
| Buzzer | +VE | D6 |
| Buzzer | -VE | GND |

> The pin table above follows the project's submitted report. The transmitter source listing in the report uses a different TRIG/ECHO ordering (`TRIG=9`, `ECHO=8`), so verify the physical wiring against the final hardware before uploading.

## Software

- Arduino IDE
- C/C++ for Arduino
- SPI
- Wire / I2C
- LiquidCrystal_I2C
- MCP CAN / MCP2515 libraries
- SoftwareSerial

## Repository Contents

```text
arduino-collision-detection-can-sms/
├── README.md
├── .gitignore
├── src/
│   ├── transmitter/
│   │   └── transmitter.ino
│   └── receiver/
│       └── receiver_report_code.ino
├── hardware/
│   └── pin_connections.md
└── docs/
    ├── project_notes.md
    ├── Project_Report.pdf
    └── images/
        ├── block_diagram.png
        ├── pin_table.png
        ├── flow_diagram.png
        └── prototype_result.png
```

## Important Source-Code Note

The receiver program included in the submitted report calls `controlMotor()` and `sendSMS()`, but the report pages provided do not include the definitions of those functions. Therefore `receiver_report_code.ino` is intentionally preserved as the **documented report code** and should not be presented as a guaranteed build-ready program until those missing function definitions are added and tested.

The transmitter listing in the report also contains a pin-definition mismatch with the separate hardware pin table. Verify the final hardware connections before deployment.

## Prototype

The submitted project report contains a photograph of the assembled prototype in the Results chapter. See `docs/images/prototype_result.png`.

## Applications

- Automotive safety prototypes
- Collision warning systems
- Emergency notification systems
- Driver monitoring prototypes
- Public transportation safety concepts
- Road-safety data collection

## Limitations

- Ultrasonic sensing can be affected by environmental and object-surface conditions.
- Sensor failure can affect system performance.
- Electromagnetic/radio-frequency interference can affect measurements.
- The prototype uses threshold-based detection and is not an automotive-certified collision avoidance system.
- GPS is mentioned in the report abstract, but GPS hardware is not shown in the reported block diagram/pin table/code.

## Future Scope

- GPS-based accident location
- More robust collision prediction
- Additional vehicle sensors
- Cloud-based accident/event logging
- Advanced vehicle-to-vehicle communication
- Integration with intelligent transportation systems

## Team

- Abhishek — 2JI22EC002
- Amit — 2JI22EC013
- Kavya — 2JI22EC053
- Manisha — 2JI22EC062

## Institution

**Jain College of Engineering, Belagavi**  
Department of Electronics and Communication Engineering  
Visvesvaraya Technological University

## Project Type

Mini Project — Electronics & Communication Engineering

## Keywords

`Arduino` `Embedded Systems` `CAN` `GSM` `Collision Detection` `Automotive Safety` `Ultrasonic Sensor` `Speed Sensor` `C/C++` `Arduino IDE`
