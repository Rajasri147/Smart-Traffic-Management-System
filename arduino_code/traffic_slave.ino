#include <Wire.h>
#include <Servo.h>

// Ultrasonic sensor and servo pins for each lane
const int trigPins[4] = {2, 4, 6, 8};     // Unique trigger pins
const int echoPins[4] = {3, 5, 7, 9};     // Unique echo pins
const int servoPins[4] = {10, 11, 12, 13};  // Servo pins

Servo tollGates[4];
int currentGreenLane = -1;
bool isGreenSignal = false;

void setup() {
  Wire.begin(8);  // Join I2C bus with address #8
  Wire.onReceive(receiveEvent);
  
  // Initialize ultrasonic sensors and servo motors
  for (int i = 0; i < 4; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
    tollGates[i].attach(servoPins[i]);
    tollGates[i].write(0);  // Initially close all gates
  }
}

void loop() {
  // Check vehicle detection for the current green lane
  if (currentGreenLane != -1) {
    int distance = getDistance(currentGreenLane);
    
    // Only open gate if green signal AND vehicle detected
    if (isGreenSignal && distance > 0 && distance < 5) {
      openTollGate(currentGreenLane);
    } else {
      // Close gate if no vehicle or not green signal
      closeTollGate(currentGreenLane);
    }
  }
  
  delay(500);
}

void receiveEvent(int howMany) {
  if (Wire.available()) {
    byte receivedData = Wire.read();
    
    // Extract lane and signal state
    currentGreenLane = receivedData >> 2;  // First 2 bits for lane
    isGreenSignal = (receivedData & 0x01); // Last bit for signal state
  }
}

int getDistance(int laneNumber) {
  // Clear the trigger pin
  digitalWrite(trigPins[laneNumber], LOW);
  delayMicroseconds(2);
  
  // Send a 10µs pulse to trigger the sensor
  digitalWrite(trigPins[laneNumber], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPins[laneNumber], LOW);
  
  // Read the echo pin and calculate the duration
  long duration = pulseIn(echoPins[laneNumber], HIGH);
  
  // Calculate the distance in centimeters
  int distance = duration * 0.034 / 2;
  
  return distance;
}

void openTollGate(int laneNumber) {
  tollGates[laneNumber].write(90);  // Open the gate
}

void closeTollGate(int laneNumber) {
  tollGates[laneNumber].write(0);   // Close the gate
}
