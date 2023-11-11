#include <Timer.h>

const int temperaturePin = A0;
const int ledPin = 13;

const int belowThresholdBlinkInterval = 250; // milliseconds
const int aboveThresholdBlinkInterval = 500; // milliseconds
const int temperatureThreshold = 30; // degrees Celsius

int currentTemperature = 0;

Timer<50> timer1; // Timer with a resolution of 1ms

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  // Set up the timer to call the blink function
  timer1.every(belowThresholdBlinkInterval, blinkBelowThreshold);
  timer1.every(aboveThresholdBlinkInterval, blinkAboveThreshold);
}

void loop() {
  // Read temperature from the LM35 sensor
  int rawTemperature = analogRead(temperaturePin);
  float voltage = (rawTemperature / 1024.0) * 5.0;
  currentTemperature = (voltage - 0.5) * 100;

  // Update the timer
  timer1.update();
}

void blinkBelowThreshold() {
  if (currentTemperature < temperatureThreshold) {
    digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle the LED state
  }
}

void blinkAboveThreshold() {
  if (currentTemperature >= temperatureThreshold) {
    digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle the LED state
  }
}
