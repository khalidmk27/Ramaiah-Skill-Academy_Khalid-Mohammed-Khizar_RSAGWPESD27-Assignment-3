# RSA Arduino Assignment

This repository contains solutions to Arduino-assignment involving various sensors, displays, and components. Each folder is organized by problem title and contains the following:

- `.png` file: Circuit connection diagram.
- `.pdf` file: Circuit layout/design.
- `.ino` file: Arduino code.

## Assignment Descriptions

### 1. Distance Measurement Display
- **Description**: Measures the distance to an object using an ultrasonic sensor and displays the result on a 7-segment display.
- **Components**: Ultrasonic sensor, 7-segment display.
- **Code**: Calculates distance and updates the display.

### 2. Smart Distance Counter
- **Description**: Increments a counter on the 7-segment display each time an object crosses a specified distance threshold detected by the ultrasonic sensor. A touch sensor resets the counter.
- **Components**: Ultrasonic sensor, touch sensor, 7-segment display.
- **Code**: Detects objects within range, updates the counter, and resets on touch.

### 3. Touch-Activated Range Finder
- **Description**: Measures distance only when the touch sensor is activated. The distance is displayed on the 7-segment display and held for 5 seconds before clearing.
- **Components**: Ultrasonic sensor, touch sensor, 7-segment display.
- **Code**: Reads and displays distance upon touch activation.

### 4. Countdown Timer with Obstacle-Activated Reset
- **Description**: A countdown timer on the 7-segment display starts with a touch sensor. If the ultrasonic sensor detects an obstacle within a specified range, the timer resets. If the countdown completes uninterrupted, an "E" is displayed.
- **Components**: Ultrasonic sensor, touch sensor, 7-segment display.
- **Code**: Starts and resets countdown based on obstacle detection.

### 5. Motion-Activated Alarm
- **Description**: Sounds a buzzer upon detecting movement with a PIR sensor and logs each detection with a timestamp in the Serial Monitor.
- **Components**: PIR sensor, buzzer.
- **Code**: Detects motion and logs timestamps.

### 6. Temperature Monitoring System
- **Description**: Reads temperature data using a DHT11 or LM35 sensor, displays it on the Serial Monitor, and sends a warning if the temperature exceeds a threshold.
- **Components**: Temperature sensor (DHT11 or LM35).
- **Code**: Monitors and outputs temperature, with threshold alerting.

### 7. People Counter with Direction Detection
- **Description**: Uses two IR sensors on either side of a doorway to count people entering and exiting, displaying the count on a 7-segment display. An ultrasonic sensor confirms direction by timing the object passing between the IR sensors.
- **Components**: IR sensors, ultrasonic sensor, 7-segment display.
- **Code**: Counts entries and exits, and verifies direction.

## Demonstration
All projects can be demonstrated using Tinkercad (online).

## Getting Started
1. Clone this repository:
   ```bash
   git clone https://github.com/khalidmk27/your-repo-name.git

2. Navigate to each problem folder for circuit details and Arduino code.

3. Upload the code to your Arduino for testing.

