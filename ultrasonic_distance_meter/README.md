# Ultrasonic Distance Meter with Alarm

**Author:** Krzysztof Szczepański  
**Course Project:** Microprocessor Technology 2  
**Field of Study:** Electronics and Telecommunications (3rd Year), AGH University of Krakow 

## Project Overview
This repository contains a microprocessor-based project (Project No. 20) developed as part of the Microprocessor Technology 2 course. The main objective was to design and implement an ultrasonic distance meter featuring selectable measurement units and a configurable alarm system to warn users of nearby obstacles.

## Features
* **Real-time Distance Measurement:** Utilizes the HC-SR04 ultrasonic sensor and echolocation principles. The system measures the time-of-flight of the reflected wave by counting clock cycles using the microcontroller's internal timer, then converts it into a distance value.
* **Selectable Units:** Users can toggle between meters, centimeters, millimeters, or inches using the keypad.
* **Adjustable Alarm Threshold:** Features a "too close" warning with a threshold that can be smoothly adjusted using the on-board capacitive touch slider. The current threshold is displayed in brackets on the screen.
* **Acoustic Alarm (DDS):** If the measured distance falls below the set limit, the device triggers an audible warning signal. This signal is generated via Direct Digital Synthesis (DDS) through the D/A converter (DAC) for precise frequency control.

## Hardware Components
The system is built using the following hardware:
* **Microcontroller:** NXP KL05Z / MKL05Z32VFM4 (FRDM-KL05Z platform) 
* **Distance Sensor:** HC-SR04p Ultrasonic sensor 
* **Display:** 2x16 LCD with HD44780U controller 
* **Input:** 4x4 Matrix Keypad (HW-834) and Capacitive Touch Slider 
* **Audio Output:** WSR-04489 Speaker 

## Pinout Configuration
| Component | Pin (Module) | Pin (Microcontroller / Power) |
| :--- | :--- | :--- |
| Keypad | C4 | PTA9 |
| Keypad | R4 | GND |
| Keypad | C3 | PTA10 |
| Keypad | C2 | PTA11 |
| Keypad | C1 | PTA12 |
| Speaker | 5V | +5V |
| Speaker | GND | GND |
| Speaker | audio_in | PTB1 |
| LCD Display | SDA | PTB4 |
| LCD Display | SCL | PTB3 |
| LCD Display | VCC | +5V |
| LCD Display | GND | GND |
| HC-SR04 Meter | VCC | +3.3V |
| HC-SR04 Meter | GND | GND |
| HC-SR04 Meter | Trigger | PTB5 |
| HC-SR04 Meter | Echo | PTB7 |

## User Manual
1. **Startup:** Upon power-up, select your preferred measurement unit (m, cm, mm, inches) by pressing the corresponding buttons (S1 to S4) on the keypad.
2. **Monitoring:** The LCD will display the current distance to the obstacle and the set alarm threshold in brackets.
3. **Threshold Adjustment:** Slide your finger across the touch panel (slider) to change the alarm limit. The new value is saved once you release your finger.
4. **Alarm Trigger:** The device will emit a stable warning tone if an object is detected within the defined limit.

## Source Code & Libraries
The project utilizes specialized drivers and libraries developed during laboratory sessions:
* `Klaw.h/c`: Keypad handling.
* `TPM.h/c`: Hardware timer management (for pulse measurement).
* `DAC.h/c`: Digital-to-Analog converter control for audio synthesis.
* `Tsi.h/c`: Capacitive Touch Slider interface.
* `Lcd1602.h/c`: LCD display driver.
* `i2c.h/c`: I2C bus implementation for display communication.
* `frdm_bsp.h`: Board Support Package providing global definitions and macros.
* `MKL05Z4.h`: Manufacturer-provided header with register definitions for the KL05Z.
