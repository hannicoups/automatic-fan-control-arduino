# Automatic Fan Control using Arduino Uno

## Description
Prototype automatic fan control system using Arduino Uno, DHT11, LDR sensor, relay module, and LCD I2C to monitor room temperature and control DC fan automatically based on average temperature calculation.

## Features
- Real-time temperature monitoring
- Automatic fan control
- Average temperature calculation
- LCD monitoring
- Light detection using LDR

## Components
- Arduino Uno
- DHT11
- Relay Module
- LCD I2C
- LDR Module
- DC Fan
- Power Adapter

## System Logic
The system reads room temperature every 5 seconds using the DHT11 sensor. The average value from 10 readings is used as the decision parameter to activate or deactivate the DC fan automatically using a relay module.

## Author
Alyaa Nur Hanifah