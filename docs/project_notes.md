# Project Notes

## Project Title

Accident Detection Using CAN Protocol and SMS Alert

## Project Overview

This project is an embedded safety prototype that uses Arduino, CAN communication, sensors, a buzzer, motor control and GSM SMS alerts.

The transmitter measures distance and speed and sends the information through the CAN communication link. The receiver processes the received information and provides collision warnings and motor control.

## Main Hardware

- Arduino Uno R3
- Ultrasonic Sensor
- Speed Sensor
- CAN Module
- GSM Module
- 16×2 I2C LCD
- Buzzer
- DC Motor
- Potentiometer

## Main Functions

- Distance measurement
- Speed monitoring
- CAN-based data transmission
- Collision warning
- Motor control
- LCD monitoring
- GSM SMS alert

## Project Logic

```text
Sensors
   ↓
Transmitter Arduino
   ↓
CAN Communication
   ↓
Receiver Arduino
   ↓
Collision / Speed Decision
   ↓
Buzzer + Motor + GSM SMS
