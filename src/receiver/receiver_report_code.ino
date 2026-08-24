#include <SPI.h>
#include <mcp2515.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define MOTOR_IN1 3
#define MOTOR_IN2 4
#define MOTOR_ENA 5
#define BUZZER_PIN 6

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial gsm(7, 8); // RX, TX for GSM Module

struct can_frame canMsg;
MCP2515 mcp2515(10);

bool smsSent = false;

void setup() {
  Serial.begin(9600);
  gsm.begin(9600);

  lcd.begin();
  lcd.backlight();

  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_ENA, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS);
  mcp2515.setNormalMode();

  // GSM Initialization
  gsm.println("AT");
  delay(1000);

  gsm.println("AT+CMGF=1");
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Receiver Ready");
  delay(1000);
  lcd.clear();
}

void loop() {

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {

    int distance = canMsg.data[0];
    int motorSpeed = canMsg.data[1];

    // Display received data
    lcd.setCursor(0, 0);
    lcd.print("Dist: ");
    lcd.print(distance);
    lcd.print("cm");

    lcd.setCursor(0, 1);
    lcd.print("Speed: ");
    lcd.print(motorSpeed);

    // Collision warning
    if (distance < 20) {

      digitalWrite(BUZZER_PIN, HIGH);

      controlMotor(0);

    } else {

      digitalWrite(BUZZER_PIN, LOW);

      controlMotor(motorSpeed);
    }

    // Send SMS if motor speed exceeds threshold
    if (motorSpeed > 200 && !smsSent) {

      sendSMS("Alert: Motor speed exceeded threshold! Check system.");

      smsSent = true;
    }

    // Reset SMS condition
    if (motorSpeed <= 200) {

      smsSent = false;
    }
  }

  delay(100);
}

/*
 * NOTE:
 * The original project report references controlMotor()
 * and sendSMS(), but their function definitions are not
 * included in the provided receiver-code pages.
 *
 * These functions must be implemented and tested before
 * using this sketch as a complete build-ready program.
 */
