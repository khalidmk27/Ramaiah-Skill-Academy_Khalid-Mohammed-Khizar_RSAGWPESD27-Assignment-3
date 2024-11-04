// IR sensors and ultrasonic sensor pins
const int IR_Left = 2;
const int IR_Right = 3;
const int trigPin = A0;
const int echoPin = A1;

// 7-segment display segment and power pins
const byte SEGMENT_PINS[8] = {9, 8, 7, 6, 2, 3, 4, 5};
const byte POWER_PINS[4] = {10, 11,12, 13};

// Segment bitwise patterns for each LED segment
const unsigned int DIGITS[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

int peopleCount = 0; // Counter for people
bool leftTriggered = false;
bool rightTriggered = false;
unsigned long passStartTime;

void setup() {
    Serial.begin(9600);

    // Set up IR sensors
    pinMode(IR_Left, INPUT);
    pinMode(IR_Right, INPUT);

    // Set up ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Set up 7-segment display pins
    for (int i = 0; i < 8; i++) {
        pinMode(SEGMENT_PINS[i], OUTPUT);
    }
    for (int i = 0; i < 4; i++) {
        pinMode(POWER_PINS[i], OUTPUT);
    }

    displayNumber(peopleCount); // Initialize display
}

void loop() {
    // Check if the left IR sensor detects movement
    if (digitalRead(IR_Left) == LOW) {
        if (!leftTriggered) {
            leftTriggered = true;
            passStartTime = millis(); // Start timing the pass
            Serial.println("Left IR sensor triggered");
        }
    } else {
        leftTriggered = false;
    }

    // Check if the right IR sensor detects movement
    if (digitalRead(IR_Right) == LOW) {
        if (!rightTriggered) {
            rightTriggered = true;
            if (millis() - passStartTime < 1000) { // If pass time is short, likely a quick pass-through
                confirmDirection();
            }
            Serial.println("Right IR sensor triggered");
        }
    } else {
        rightTriggered = false;
    }

    // Continuously display the current people count
    displayNumber(peopleCount);
}

// Function to confirm entry or exit direction
void confirmDirection() {
    unsigned int distance = measureDistance();

    if (distance < 50) { // If ultrasonic detects an object within range
        if (leftTriggered && rightTriggered) {
            peopleCount++; // Left-to-right sequence means entry
            Serial.println("Person entered. People count: " + String(peopleCount));
        } else if (rightTriggered && leftTriggered) {
            peopleCount--; // Right-to-left sequence means exit
            Serial.println("Person exited. People count: " + String(peopleCount));
        }
        displayNumber(peopleCount);
    }
}

// Measure distance with ultrasonic sensor
unsigned int measureDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    return duration * 0.034 / 2;
}

// Display a number on 7-segment display
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

// Display a single digit at specific position
void displayDigit(int digit, int position) {
    for (int i = 0; i < 4; i++) {
        digitalWrite(POWER_PINS[i], LOW); // Turn off all digits
    }
    digitalWrite(POWER_PINS[position], HIGH); // Activate specific digit

    for (int i = 0; i < 8; i++) {
        if (DIGITS[digit] & (1 << i)) {
            digitalWrite(SEGMENT_PINS[i], LOW);
        } else {
            digitalWrite(SEGMENT_PINS[i], HIGH);
        }
    }
}