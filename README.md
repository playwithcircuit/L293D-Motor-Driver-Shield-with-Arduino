# L293D Motor Driver Shield with Arduino – Complete Guide

This repository demonstrates how to use the **L293D Motor Driver Shield** with Arduino to control **DC motors, Servo motors, and Stepper motors**. It includes hardware setup, pin configurations, and connection details for practical implementation.

---

## 📌 Overview

The L293D Motor Driver Shield simplifies motor control by providing an easy interface between Arduino and motors using **dual H-bridge drivers**. It allows:

* Control of **4 DC motors** OR
* **2 Stepper motors** and
* **2 Servo motors**

---

## 🔧 Hardware Overview
![L293D Motor Driver Shield Hardware Overview](https://playwithcircuit.com/wp-content/uploads/2024/07/L293D-Motor-Driver-Shield-Hardware-Overview.webp)
* Dual L293D ICs (H-Bridge motor drivers)
* 4 motor output channels (M1–M4)
* 2 servo headers (PWM controlled)
* External power terminal (EXT_PWR)
* Power selection jumper (PWR)
* Access to Arduino pins (A0–A5, Vin, GND, 5V)

---

## 📍 Pinout Details
![L293D Motor Driver Pinout](https://playwithcircuit.com/wp-content/uploads/2024/07/L293D-Motor-Driver-Shield-Pinout-768x432.webp)
### DC Motor Outputs

| Terminal | Description     |
| -------- | --------------- |
| M1       | Motor Channel 1 |
| M2       | Motor Channel 2 |
| M3       | Motor Channel 3 |
| M4       | Motor Channel 4 |

* Voltage Range: **4.5V – 24V**
* Current: **600mA per channel (1.2A peak)**

---

### Stepper Motor Connections

| Stepper   | Connected Terminals |
| --------- | ------------------- |
| Stepper 1 | M1 & M2             |
| Stepper 2 | M3 & M4             |

---

### Servo Motor Connections

| Servo Port | Arduino Pin |
| ---------- | ----------- |
| SER1       | PWM pin 10 of the Arduino         |
| SER2       | PWM pin 9 of the Arduino          |

* Powered from Arduino 5V
* Includes onboard capacitor for stability

---

### Power Configuration

| Mode             | Description                      |
| ---------------- | -------------------------------- |
| Jumper Connected | Single supply (Arduino + Motors) |
| Jumper Removed   | Separate supply (Recommended)    |

⚠️ **Important:** Never keep jumper connected while using external motor supply.

---

## 🧰 Complete Bill of Materials (BOM)

### Core Components

| Component                 | Quantity | Specification         |
| ------------------------- | -------- | --------------------- |
| Arduino UNO R3            | 1        | Microcontroller board |
| L293D Motor Driver Shield | 1        | Arduino compatible    |
| USB Cable                 | 1        | Type A to B           |

---

### Motors

| Component     | Quantity | Specification |
| ------------- | -------- | ------------- |
| DC Motor      | 1        | 5V            |
| Servo Motor   | 1        | SG90, 5V      |
| Stepper Motor | 1        | 28BYJ-48, 5V  |

---

### Input Components

| Component     | Quantity | Specification    |
| ------------- | -------- | ---------------- |
| Push Buttons  | 3        | DC motor control |
| Push Buttons  | 2        | Servo control    |
| Potentiometer | 1        | 10KΩ             |

---

### Display

| Component   | Quantity | Specification |
| ----------- | -------- | ------------- |
| LCD Display | 1        | 16x2 with I2C |

---

### Power Supply

| Component       | Quantity | Specification       |
| --------------- | -------- | ------------------- |
| DC Adapter      | 1        | 12V (Arduino input) |
| External Supply | 1        | 5V (Motor driver)   |

---

### Miscellaneous

| Component    | Quantity |
| ------------ | -------- |
| Breadboard   | 1        |
| Jumper Wires | ~20      |

---

## ⚙️ Software Requirements

* Arduino IDE (v2.1.1 or above)
* Servo Library (built-in)
* LiquidCrystal I2C Library (v1.1.2)

---

# 🔌 Project 1: DC Motor Control

### Connections

![Wiring of DC motor with L293D shield and Arduino UNO](https://playwithcircuit.com/wp-content/uploads/2024/07/Wiring-of-DC-motor-with-L293D-shield-and-Arduino-UNO-768x432.webp)

| Arduino Pin | Connection            |
| ----------- | --------------------- |
| 5V          | LCD VCC, POT Pin 1    |
| GND         | LCD GND, POT Pin 3    |
| A0          | pin 2 of POT        |
| A1          | Clockwise Button      |
| A2          | Anti-clockwise Button |
| A3          | Stop Button           |
| SDA         | LCD SDA               |
| SCL         | LCD SCL               |

* Motor connected to **M3 of the shield**
* External 5V supply to **EXT_PWR**
* PWR jumper **removed**

---

### Functionality

* Speed controlled via potentiometer (PWM)
* Direction via push buttons
* LCD displays status

---

# 🔌 Project 2: Servo Motor Control

### Connections

![Wiring of Servo motor with L293D shield and Arduino UNO](https://playwithcircuit.com/wp-content/uploads/2024/07/Wiring-of-Servo-Motor-with-L293D-shield-and-Arduino-UNO-768x432.webp)

| Arduino Pin | Connection     |
| ----------- | -------------- |
| 5V          | Vcc pin of LCD and pin 1 of POT   |
| GND         | Gnd pin of LCD and pin 3 of POT        |
| A0          | pin 2 of POT            |
| A1          | Forward Button |
| A2          | Reverse Button |
| SDA         | SDA pin of LCD            |
| SCL         | SCL pin of LCD            |

* Servo connected to **SER1 (Pin D10)**

---

### Functionality

* Button-based directional movement
* Smooth motion using PWM
* Initial position: center

---

# 🔌 Project 3: Stepper Motor Control

### Connections

![Wiring of Stepper motor with L293D shield and Arduino UNO](https://playwithcircuit.com/wp-content/uploads/2024/07/Controlling-28BYJ-48-Stepper-Motor-with-Arduino-UNO-and-L293D-Motor-Driver-Shield--768x432.webp)

| Arduino Pin | Connection     |
| ----------- | -------------- |
| 5V          | Vcc pin of LCD and pin 1 of POT     |
| GND         | 	Gnd pin of LCD and pin 3 of POT  |
| A0          | pin 2 of POT            |
| A1          | Clockwise rotation Button      |
| A2          | Anti-Clockwise rotation Button |
| A3          | Stop Button          |
| SDA         | SDA pin of LCD           |
| SCL         | SCL pin of LCD            |

* Stepper connected to **M3 & M4**
* External 5V supply required

---

### Functionality

* Step-based rotation control
* Speed via potentiometer
* Direction via buttons

---

## 💡 Important Notes

* Analog pins (A1–A3) are used as digital inputs
* Digital pins are mostly occupied by the shield
* Always verify power configuration before powering
* Incorrect wiring in stepper motors can cause damage

---

## 📚 Full Tutorial

For complete step-by-step instructions, code, and detailed explanation visit _Play with Circuit_:

👉 https://playwithcircuit.com/l293d-motor-driver-shield-arduino-tutorial/
