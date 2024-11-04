const int pirPin = 2;     // PIR sensor output pin
const int buzzerPin = 3;  // Buzzer pin
int pirState = LOW;       // Current state of the PIR sensor (LOW means no motion)
unsigned long lastDetectionTime = 0; // Store the last detection time

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int motionDetected = digitalRead(pirPin);

  if (motionDetected == HIGH && pirState == LOW) {
    // If motion is detected and PIR was previously in LOW state
    digitalWrite(buzzerPin, HIGH); // Activate the buzzer
    lastDetectionTime = millis();  // Get the current timestamp
    Serial.print("Movement detected at: ");
    Serial.print(lastDetectionTime / 1000); // Convert milliseconds to seconds
    Serial.println(" seconds");

    pirState = HIGH; // Update PIR state to HIGH
  } 
  else if (motionDetected == LOW && pirState == HIGH) {
    // If no motion is detected and PIR was previously in HIGH state
    digitalWrite(buzzerPin, LOW); // Deactivate the buzzer
    pirState = LOW; // Update PIR state to LOW
  }
}
