// Define pins for ultrasonic sensor
const int trigPin = A0; // Trig pin for ultrasonic sensor
const int echoPin = A1; // Echo pin for ultrasonic sensor

// Push button pin
const int buttonPin = 2; // Push button pin

// 7-segment display segment and power pins
const byte SEGMENT_PINS[8] = {9, 8, 7, 6, 2, 3, 4, 5};
const byte POWER_PINS[4] = {10, 11, 12, 13};
const byte SEGMENT_LENGTH = sizeof(SEGMENT_PINS) / sizeof(byte);
const byte POWER_LENGTH = sizeof(POWER_PINS) / sizeof(byte);

// Segment bitwise patterns for each LED segment
const unsigned int SEGMENTS[8] = {
    1 << 0, // middle
    1 << 1, // top left
    1 << 2, // top
    1 << 3, // top right
    1 << 4, // dot
    1 << 5, // bottom right
    1 << 6, // bottom
    1 << 7  // bottom left
};

// Digit patterns for numbers 0-9
const unsigned int DIGITS[10] = {
    (SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5] | SEGMENTS[6] | SEGMENTS[7]), // 0
    (SEGMENTS[3] | SEGMENTS[5]), // 1
    (SEGMENTS[0] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[6] | SEGMENTS[7]), // 2
    (SEGMENTS[0] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5] | SEGMENTS[6]), // 3
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[3] | SEGMENTS[5]), // 4
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[5] | SEGMENTS[6]), // 5
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[5] | SEGMENTS[6] | SEGMENTS[7]), // 6
    (SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5]), // 7
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5] | SEGMENTS[6] | SEGMENTS[7]), // 8
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5] | SEGMENTS[6]) // 9
};

// Threshold distance in cm to increment the counter
const int thresholdDistance = 10;
int counter = 0; // Counter to track objects crossing the threshold
bool objectDetected = false;

void setup() {
    // Set up serial monitor
    Serial.begin(9600);

    // Set up the ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Set up the push button pin
    pinMode(buttonPin, INPUT_PULLUP);

    // Set up 7-segment display pins
    for (byte i = 0; i < POWER_LENGTH; i++) {
        pinMode(POWER_PINS[i], OUTPUT);
        digitalWrite(POWER_PINS[i], LOW);
    }
    for (byte i = 0; i < SEGMENT_LENGTH; i++) {
        pinMode(SEGMENT_PINS[i], OUTPUT);
        digitalWrite(SEGMENT_PINS[i], HIGH);
    }
}

void loop() {
    // Check if push button is pressed to reset the counter
    if (digitalRead(buttonPin) == HIGH) {
        counter = 0;
        Serial.println("Counter reset.");
        displayNumber(counter);
        delay(300); // Debounce delay
    }

    // Measure distance using the ultrasonic sensor
    unsigned int distance = measureDistance();

    // Increment counter if an object is within the threshold and hasn't been counted yet
    if (distance < thresholdDistance && !objectDetected) {
        counter++;
        objectDetected = true;
        Serial.print("Object detected! Counter: ");
        Serial.println(counter);
        displayNumber(counter);
        delay(500); // Debounce delay for counting
    }

    // Reset objectDetected if no object is within the threshold distance
    if (distance >= thresholdDistance) {
        objectDetected = false;
    }

    // Display the counter on the 7-segment display continuously
    displayNumber(counter);
}

// Function to measure distance with the ultrasonic sensor
unsigned int measureDistance() {
    // Clear the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Set the trigPin high for 10us to send pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Read echoPin, get duration
    long duration = pulseIn(echoPin, HIGH);
    
    // Calculate the distance in cm
    return duration * 0.034 / 2;
}

// Function to display a number on the 7-segment display
void displayNumber(int number) {
    int thousands = number / 1000;
    int hundreds = (number / 100) % 10;
    int tens = (number / 10) % 10;
    int units = number % 10;

    displayDigit(thousands, 0);
    delay(5);
    displayDigit(hundreds, 1);
    delay(5);
    displayDigit(tens, 2);
    delay(5);
    displayDigit(units, 3);
    delay(5);
}

// Function to display a single digit on a specific position
void displayDigit(int digit, int position) {
    // Activate only the specified digit (position)
    for (int i = 0; i < 4; i++) digitalWrite(POWER_PINS[i], LOW); // Turn off all digits
    digitalWrite(POWER_PINS[position], HIGH); // Turn on the specified digit

    // Set segments for the desired digit
    for (int i = 0; i < 8; i++) {
        if (DIGITS[digit] & SEGMENTS[i]) {
            digitalWrite(SEGMENT_PINS[i], LOW);
        } else {
            digitalWrite(SEGMENT_PINS[i], HIGH);
        }
    }
}
