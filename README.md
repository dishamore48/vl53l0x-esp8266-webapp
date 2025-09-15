# vl53l0x-esp8266-webapp
# Laser-Based Distance Measurement System (VL53L0X + ESP8266 + Web App)

An IoT project that measures distances with a VL53L0X laser sensor, displays readings on an I²C LCD, and transmits them via ESP8266 Wi-Fi to a web interface where the values can be stored and labeled.

---

 📖 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Hardware Used](#hardware-used)
- [Wiring / Connections](#wiring--connections)
- [Software / Libraries](#software--libraries)
- [Setup Instructions](#setup-instructions)

---

📝 Overview
This system allows you to measure distances using a VL53L0X Time-of-Flight sensor.  
The ESP8266 collects the data, displays it locally on a 16x2 I²C LCD, and serves a simple web interface (using ESPAsyncWebServer) where readings are displayed and labeled in real time.

---

✨ Features
- Real-time laser distance measurement.
- Local LCD display of measured values.
- Wi-Fi transmission of data to a web interface.
- Ability to store and label measurements.
- Compact hardware footprint.

---

 🔧 Hardware Used
| Component | Description |
|-----------|-------------|
| VL53L0X Time-of-Flight Sensor | Measures distance using laser light. |
| ESP8266 (NodeMCU) | Microcontroller + Wi-Fi module. |
| 16x2 LCD with I²C Backpack | Displays measurements locally. |
| Power Supply | USB or battery pack. |

---

🔌 Wiring / Connections
| From (Device) | To (ESP8266 Pin) | Notes |
|---------------|-----------------|-------|
| VL53L0X SDA | D2 (GPIO4) | I²C Data |
| VL53L0X SCL | D1 (GPIO5) | I²C Clock |
| VL53L0X VCC | 3V3 | Power for sensor |
| VL53L0X GND | GND | Common ground |
| LCD SDA | D2 (GPIO4) | Shares I²C bus |
| LCD SCL | D1 (GPIO5) | Shares I²C bus |
| LCD VCC | VIN / 5V | Power for LCD |
| LCD GND | GND | Common ground |

---

🛠 Software / Libraries
- Arduino IDE / PlatformIO
- ESPAsyncWebServer
- Wire.h
- VL53L0X library
- LiquidCrystal_I2C library

---

🚀 Setup Instructions
1. **Hardware** – Connect components as per wiring table above.
2. **Code Upload** – Open the Arduino sketch in Arduino IDE, select ESP8266 board, and upload.
3. **Wi-Fi Configuration** – Update your SSID and password in the sketch.
4. **Access Web App** – Once ESP8266 connects, open the IP shown in Serial Monitor to view the web interface.

---

🖼 Screenshots
_Add screenshots of your web interface and hardware setup here._

---




