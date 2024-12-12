#include <Wire.h>

// Traffic light pins for each lane
const int lanes[4][3] = {
  {3, 4, 5},    // Lane 1: Green, Yellow, Red
  {6, 7, 8},    // Lane 2: Green, Yellow, Red
  {9, 10, 11},  // Lane 3: Green, Yellow, Red
  {12, 13, A0}  // Lane 4: Green, Yellow, Red
};

// Traffic light states
enum LightState {
  GREEN,
  YELLOW,
  RED
};

int currentLaneIndex = 0;
unsigned long previousMillis = 0;
const long interval = 5000;  // 5 seconds per light cycle

void setup() {
  Wire.begin(); // Initialize I2C as master
  
  // Setup all traffic light pins
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      // Use pinMode for A0 as a digital pin
      if (lanes[i][j] == A0) {
        pinMode(A0, OUTPUT);
      } else {
        pinMode(lanes[i][j], OUTPUT);
      }
    }
  }
  
  // Initially set all lanes to red
  setAllLanesToRed();
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    cycleTrafficLights();
  }
}

void cycleTrafficLights() {
  // Reset all lanes to red first
  setAllLanesToRed();
  
  // Set the current lane to green
  setLaneLight(currentLaneIndex, GREEN);
  
  // Calculate the next lane index (wrapping around to 0 if it reaches 4)
  int yellowLaneIndex = (currentLaneIndex + 1) % 4;
  
  // Set the next consecutive lane to yellow
  setLaneLight(yellowLaneIndex, YELLOW);
  
  // Prepare data to send to slave Arduino
  byte dataToSend = (currentLaneIndex << 2) | 0x01;  // Encode lane and green signal state
  
  // Send I2C signal to vehicle detection Arduino
  Wire.beginTransmission(8);
  Wire.write(dataToSend);
  Wire.endTransmission();
  
  // Move to the next lane for next cycle
  currentLaneIndex = (currentLaneIndex + 1) % 4;
}

void setAllLanesToRed() {
  for (int i = 0; i < 4; i++) {
    setLaneLight(i, RED);
  }
}

void setLaneLight(int laneNumber, LightState state) {
  // Turn off all lights for this lane first
  for (int j = 0; j < 3; j++) {
    if (lanes[laneNumber][j] == A0) {
      digitalWrite(A0, LOW);
    } else {
      digitalWrite(lanes[laneNumber][j], LOW);
    }
  }
  
  // Set the appropriate light
  switch(state) {
    case GREEN:
      if (lanes[laneNumber][0] == A0) {
        digitalWrite(A0, HIGH);
      } else {
        digitalWrite(lanes[laneNumber][0], HIGH);
      }
      break;
    case YELLOW:
      if (lanes[laneNumber][1] == A0) {
        digitalWrite(A0, HIGH);
      } else {
        digitalWrite(lanes[laneNumber][1], HIGH);
      }
      break;
    case RED:
      if (lanes[laneNumber][2] == A0) {
        digitalWrite(A0, HIGH);
      } else {
        digitalWrite(lanes[laneNumber][2], HIGH);
      }
      break;
  }
}
