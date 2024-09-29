# Arduino Tilt Signal Project

This project demonstrates how to use an accelerometer (ADXL345) with an Arduino to detect tilt in both left and right directions. Based on the tilt, the system activates corresponding LEDs and buzzes a buzzer. Additionally, an LCD display shows arrows indicating the direction of the tilt.

## Components Used
- Arduino Uno
- ADXL345 Accelerometer
- 16x2 LCD Display (I2C)
- 2 LEDs
- Buzzer
- Jumper wires

## Features
- Detect tilt using the ADXL345 accelerometer.
- Show tilt direction on an LCD screen.
- Light up LEDs and trigger a buzzer for visual and audible feedback.
- Display data via Serial Monitor.

## Setup
1. Connect the components as described in the code.
2. Upload the `tilt_signal.ino` file to your Arduino using the Arduino IDE.
3. Monitor the output via the Serial Monitor to view tilt data.

## Circuit Diagram
(Optional: Add an image of the circuit here)

## Libraries Used
- **Wire.h**: For I2C communication with the ADXL345 and LCD.
- **LiquidCrystal_I2C.h**: For controlling the 16x2 LCD display.

### Code Explanation
The Arduino reads the accelerometer data from the ADXL345 over I2C. If the Y-axis tilt exceeds a threshold, the system indicates whether the tilt is to the left or right by displaying arrows on the LCD, lighting up the appropriate LED, and sounding the buzzer.

