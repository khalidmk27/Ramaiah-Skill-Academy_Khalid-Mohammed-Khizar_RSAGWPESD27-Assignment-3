#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

#define TRIG_PIN 9
#define ECHO_PIN 10

Adafruit_7segment display = Adafruit_7segment();

void setup() {
  // Initialize the serial monitor
  Serial.begin(9600);

  // Set up ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize the 7-segment display
  display.begin(0x70); // Address for the I2C 7-segment display
  display.setBrightness(5); // Optional: set brightness (0-15)
}

void loop() {
  long duration, distance;

  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the echo response time
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in centimeters
  distance = duration * 0.034 / 2;

  // Print to serial monitor (for debugging)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Display the distance on the 4-digit 7-segment display
  if (distance < 10000) { // Ensure distance fits within display range
    display.print(distance); // Display distance directly
  } else {
    display.print(9999); // Cap display to 9999 if distance is too large
  }

  display.writeDisplay();
  delay(500); // Delay between measurements
}
