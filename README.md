# Automatic Fan Control using Arduino Uno

## Description
An automatic fan control system developed using Arduino Uno, DHT11, LDR sensor, relay module, and LCD I2C. The system monitors room temperature, calculates the average value from multiple readings, and automatically controls a DC fan based on the calculated average temperature.

## Features
- Real-time temperature monitoring using DHT11
- Average temperature calculation from 10 readings
- Automatic DC fan control using a relay module
- LCD I2C status display
- Ambient light monitoring using LDR
- Serial Monitor logging for system monitoring

## Components
- Arduino Uno
- DHT11 Temperature Sensor
- LDR (Light Dependent Resistor)
- Relay Module
- LCD I2C 16x2
- DC Fan
- 5V Power Adapter
- Breadboard
- Jumper Wires

## System Logic
1. The DHT11 sensor reads room temperature 10 times.
2. Each temperature reading is displayed on the LCD and Serial Monitor.
3. After all readings are collected, the system calculates the average temperature.
4. The LDR sensor measures the ambient light condition and classifies it as either **TERANG** or **GELAP**.
5. If the average temperature is greater than or equal to 25°C, the relay activates the DC fan automatically.
6. The LCD displays the average temperature, fan status, and light condition.
7. System information is also logged to the Serial Monitor.

## Wiring Configuration

| Component | Arduino Pin |
|------------|------------|
| DHT11 Data | D5 |
| LDR Output | A0 |
| Relay IN | D8 |
| LCD SDA | A4 |
| LCD SCL | A5 |

## Hardware Implementation

The DC fan is powered using an external 5V adapter and controlled through a relay module. This configuration prevents excessive current draw from the Arduino USB connection and improves system safety.

## Author

Alyaa Nur Hanifah
Farazahwa J Michelle  
Informatics Engineering – Telkom University