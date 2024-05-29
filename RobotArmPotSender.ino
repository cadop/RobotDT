#include <Wire.h>
#include <WiFiNINA.h>
#include <Adafruit_PWMServoDriver.h>

// Network details enter these before running 
char ssid[] = "";
char pass[] = "";


int status = WL_IDLE_STATUS;
WiFiUDP Udp;

// UDP connection info
unsigned int localPort = 8881;
String deviceID = "1";

// PWM 
#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define FREQUENCY             50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Potentiometer pins
#define basePot A0      // Base
#define shoulderPot A1  // Shoulder
#define elbowPot A2     // Elbow
#define wristPot A3     // Wrist

#define fsrPin A6      // FSR sensor
#define threshold 100  // Threshold value based on calibration

// Initial readings from potentiometers to calibrate ISAAC readings
int pot1_offset;
int pot2_offset;
int pot3_offset;
int pot4_offset;

int wrist = 12;
int elbow = 13;  // Assign Motors to pins on Servo Driver Board
int shoulder = 14;
int base = 15;

// Offset PWM values for each motor
int pwmOffsets[4] = { 0, 150, 0, 350};  // Initialize offsets to 0

String data;

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  pwm.setPWM(11, 0, 90);

  // Initialize WiFi
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(5000);
  }
  Serial.println("Connected to WiFi");
  Serial.print("Arduino IP address: ");
  Serial.println(WiFi.localIP());
  
  Udp.begin(localPort);
  pinMode(fsrPin, INPUT);

  pot1_offset = analogRead(basePot);
  pot2_offset = analogRead(shoulderPot);
  pot3_offset = analogRead(elbowPot);
  pot4_offset = analogRead(wristPot);
}

// Read potentiometer values
int pot_1;
int pot_2;
int pot_3;
int pot_4;

int fsrReading;  // Variable to store the reading

void moveMotor(int controlIn, int motorOut, int offset, bool reverse = false) {
  int potVal = analogRead(controlIn);
  int pulse_wide;
  if (reverse) {
    pulse_wide = map(potVal, 240, 800, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);  // Reverse direction
  } else {
    pulse_wide = map(potVal, 800, 240, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);  // Normal direction
  }
  pulse_wide += offset;  // Apply offset
  int pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);    // Convert pulse width to PWM value
  pwm.setPWM(motorOut, 0, pulse_width);
}

void loop() {
  moveMotor(wristPot, wrist, pwmOffsets[0]);  // Normal direction
  moveMotor(elbowPot, elbow, pwmOffsets[1], true);  // Reverse direction
  moveMotor(shoulderPot, shoulder, pwmOffsets[2], true);  // Reverse direction
  moveMotor(basePot, base, pwmOffsets[3], true);  // Reverse direction

  pot_1 = analogRead(basePot) - pot1_offset;
  pot_2 = analogRead(shoulderPot) - pot2_offset;
  pot_3 = analogRead(elbowPot) - pot3_offset;
  pot_4 = analogRead(wristPot) - pot4_offset;

  fsrReading = analogRead(fsrPin);  // Read the voltage at the FSR
  if (fsrReading < threshold) {
    //Serial.println("Powder removed");  // Print message if below threshold (remove first comment to get the powder removed message)
  }

  // Create data string
  data = String(pot_1) + "," + String(pot_2) + "," + String(pot_3) + "," + String(pot_4) + "," + String(fsrReading);
  Serial.println(data);


  Udp.beginPacket("", localPort); //enter IP address here
  Udp.write(data.c_str());
  Udp.endPacket();

}
