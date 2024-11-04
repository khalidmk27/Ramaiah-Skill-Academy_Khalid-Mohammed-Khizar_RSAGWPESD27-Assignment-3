// TMP36 Temperature Sensor Setup
const int sensorPin = A0; // TMP36 output connected to analog pin A0
const float thresholdTemp = 30.0; // Temperature threshold in Celsius

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
}

void loop() {
  // Read the analog value from the TMP36
  int sensorValue = analogRead(sensorPin);
  
  // Convert the analog value to voltage (0-5V)
  float voltage = sensorValue * (5.0 / 1023.0);
  
  // Convert voltage to temperature in Celsius
  float temperatureC = (voltage - 0.5) * 100.0;

  // Display the temperature on the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  // Check if the temperature exceeds the threshold
  if (temperatureC > thresholdTemp) {
    Serial.println("WARNING: Temperature exceeds threshold!");
  }

  delay(2000); // Wait for 2 seconds before the next reading
}
