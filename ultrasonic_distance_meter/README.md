# Ultrasonic Distance Meter with Alarm

[cite_start]**Author:** Krzysztof Szczepański [cite: 161]  
[cite_start]**Course Project:** Microprocessor Technology 2 [cite: 156]  
[cite_start]**Field of Study:** Electronics and Telecommunications (3rd Year), AGH University of Krakow [cite: 162, 170, 171]

## Project Overview
[cite_start]This repository contains a microprocessor-based project (Project No. 20) developed as part of the Microprocessor Technology 2 course[cite: 157]. [cite_start]The main objective was to design and implement an ultrasonic distance meter featuring selectable measurement units and a configurable alarm system to warn users of nearby obstacles[cite: 169].

## Features
* [cite_start]**Real-time Distance Measurement:** Utilizes the HC-SR04 ultrasonic sensor and echolocation principles[cite: 189]. [cite_start]The system measures the time-of-flight of the reflected wave by counting clock cycles using the microcontroller's internal timer, then converts it into a distance value[cite: 190, 191].
* [cite_start]**Selectable Units:** Users can toggle between meters, centimeters, millimeters, or inches using the keypad[cite: 159, 183, 191].
* [cite_start]**Adjustable Alarm Threshold:** Features a "too close" warning with a threshold that can be smoothly adjusted using the on-board capacitive touch slider[cite: 160, 185, 192]. [cite_start]The current threshold is displayed in brackets on the screen[cite: 184].
* [cite_start]**Acoustic Alarm (DDS):** If the measured distance falls below the set limit, the device triggers an audible warning signal[cite: 187, 193]. [cite_start]This signal is generated via Direct Digital Synthesis (DDS) through the D/A converter (DAC) for precise frequency control[cite: 160, 194].

## Hardware Components
[cite_start]The system is built using the following hardware[cite: 174]:
* [cite_start]**Microcontroller:** NXP KL05Z / MKL05Z32VFM4 (FRDM-KL05Z platform) [cite: 175]
* [cite_start]**Distance Sensor:** HC-SR04p Ultrasonic sensor [cite: 177]
* [cite_start]**Display:** 2x16 LCD with HD44780U controller [cite: 175]
* [cite_start]**Input:** 4x4 Matrix Keypad (HW-834) [cite: 175] [cite_start]and Capacitive Touch Slider [cite: 192]
* [cite_start]**Audio Output:** WSR-04489 Speaker [cite: 176]

## Pinout Configuration
| Component | Pin (Module) | Pin (Microcontroller / Power) |
| :--- | :--- | :--- |
| Keypad | C4 | [cite_start]PTA9 [cite: 181] |
| Keypad | R4 | [cite_start]GND [cite: 181] |
| Keypad | C3 | [cite_start]PTA10 [cite: 181] |
| Keypad | C2 | [cite_start]PTA11 [cite: 181] |
| Keypad | C1 | [cite_start]PTA12 [cite: 181] |
| Speaker | 5V | [cite_start]+5V [cite: 181] |
| Speaker | GND | [cite_start]GND [cite: 181] |
| Speaker | audio_in | [cite_start]PTB1 [cite: 181] |
| LCD Display | SDA | [cite_start]PTB4 [cite: 181] |
| LCD Display | SCL | [cite_start]PTB3 [cite: 181] |
| LCD Display | VCC | [cite_start]+5V [cite: 181] |
| LCD Display | GND | [cite_start]GND [cite: 181] |
| HC-SR04 Meter | VCC | [cite_start]+3.3V [cite: 181] |
| HC-SR04 Meter | GND | [cite_start]GND [cite: 181] |
| HC-SR04 Meter | Trigger | [cite_start]PTB5 [cite: 181] |
| HC-SR04 Meter | Echo | [cite_start]PTB7 [cite: 181] |

## User Manual
1. [cite_start]**Startup:** Upon power-up, select your preferred measurement unit (m, cm, mm, inches) by pressing the corresponding buttons (S1 to S4) on the keypad[cite: 183].
2. [cite_start]**Monitoring:** The LCD will display the current distance to the obstacle and the set alarm threshold in brackets[cite: 184].
3. [cite_start]**Threshold Adjustment:** Slide your finger across the touch panel (slider) to change the alarm limit[cite: 185, 192]. [cite_start]The new value is saved once you release your finger[cite: 185].
4. [cite_start]**Alarm Trigger:** The device will emit a stable warning tone if an object is detected within the defined limit[cite: 187, 193, 194].

## Source Code & Libraries
[cite_start]The project utilizes specialized drivers and libraries developed during laboratory sessions[cite: 197]:
* [cite_start]`Klaw.h/c`: Keypad handling[cite: 198].
* [cite_start]`TPM.h/c`: Hardware timer management (for pulse measurement)[cite: 198].
* [cite_start]`DAC.h/c`: Digital-to-Analog converter control for audio synthesis[cite: 199].
* [cite_start]`Tsi.h/c`: Capacitive Touch Slider interface[cite: 200].
* [cite_start]`Lcd1602.h/c`: LCD display driver[cite: 201].
* [cite_start]`i2c.h/c`: I2C bus implementation for display communication[cite: 202].
* [cite_start]`frdm_bsp.h`: Board Support Package providing global definitions and macros[cite: 202].
* [cite_start]`MKL05Z4.h`: Manufacturer-provided header with register definitions for the KL05Z[cite: 204].