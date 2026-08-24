#include <SPI.h>
#include <mcp_can.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin Definitions
#define TRIG_PIN 9
#define ECHO_PIN 8
#define SPEED_PIN 2
#define CAN_CS 10

// Initialize I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialize CAN module
MCP_CAN CAN(CAN_CS);

// Variables for speed sensor
volatile unsigned long lastTime = 0;
volatile float speed = 0.0;

// Function prototypes
float measureDistance();
void calculateSpeed();

void setup() {
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("System Starting");
  delay(2000);
  lcd.clear();

  // Setup ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Setup speed sensor
  pinMode(SPEED_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SPEED_PIN),
                  calculateSpeed, FALLING);

  // Initialize CAN module
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN Module Initialized");
    lcd.print("CAN Ready");
  } else {
    Serial.println("CAN Module Initialization Failed!");
    lcd.print("CAN Fail");
    while (1);
  }

  CAN.setMode(MCP_NORMAL);
  lcd.clear();
}

void loop() {
  // Measure distance
  float distance = measureDistance();

  // Prepare data to be sent via CAN
  byte data[8];
  data[0] = (byte)(distance);
  data[1] = (byte)(speed);

  // Send data via CAN
  if (CAN.sendMsgBuf(0x100, 0, 2, data) == CAN_OK) {
    Serial.print("Data Sent: Distance = ");
    Serial.print(distance);
    Serial.print(" cm, Speed = ");
    Serial.print(speed);
    Serial.println(" m/s");
  } else {
    Serial.println("Data Send Failed!");
  }

  // Display distance and speed on LCD
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm");

  lcd.setCursor(0, 1);
  lcd.print("Speed: ");
  lcd.print(speed);
  lcd.print(" m/s");

  delay(500);
}

// Function to measure distance using ultrasonic sensor
float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  float distance = (duration * 0.0343) / 2;

  return distance;
}

// Function to calculate speed using speed sensor
void calculateSpeed() {
  unsigned long currentTime = micros();

  if (lastTime != 0) {
    speed = 0.05 /
            ((currentTime - lastTime) / 1000000.0);
  }

  lastTime = currentTime;
}
