#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object

//NOTICE: we are using the A0 and A2 analog pins, as the Arduino (Nano in my case) doesn't have any more digital pins left.
const int pingPin = 14; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 15; // Echo Pin of Ultrasonic Sensor

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {13, 10, 9, 7};
  byte segmentPins[] = {12, 8, 5, 3, 2, 11, 6, 4};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md (of the library) for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
  digitalWrite(pingPin, HIGH);
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

static int storedvalue;

void loop() {
  long duration, cm;
  if (millis() % 300 == 0) //refesh rate of 300ms
  {
     pinMode(pingPin, OUTPUT);
     digitalWrite(pingPin, LOW);
     delayMicroseconds(2);
     digitalWrite(pingPin, HIGH);
     delayMicroseconds(20);
     digitalWrite(pingPin, LOW);
     pinMode(echoPin, INPUT);
     duration = pulseIn(echoPin, HIGH);
     cm = microsecondsToCentimeters(duration);
     storedvalue = cm;
  }
   sevseg.setNumber(storedvalue);
   sevseg.refreshDisplay(); // Must run repeatedly
}
