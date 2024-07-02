# Iot-GreenHouse-Firmware
Source files for MVP #1 Iot GreenHouse - Firmware 

## Overview

SOW is an IoT device firmware project based on the ESP32-C6 microcontroller. This firmware enables connectivity and control for the SOW IoT device, facilitating seamless integration with various IoT platforms and services.

## Features

- **Wi-Fi and Bluetooth Connectivity**: Leveraging the capabilities of the ESP32-C6 for robust wireless communication.
- **Sensor Integration**: Supports various sensors for data acquisition and monitoring.
- **OTA Updates**: Firmware updates over-the-air to ensure the device is always up-to-date.
- **Power Management**: Optimized power consumption for battery-operated applications.
- **Secure Communication**: Implements secure protocols to protect data integrity and privacy.

## Getting Started

### Prerequisites

- **Hardware**: SOW IoT device based on ESP32-C6.
- **Software**: Arduino IDE with ESP32 support.
- **Arduino CLI**: arduino command line interface [https://arduino.github.io/arduino-cli/0.35/installation/]

### Installation

1. **Clone the Repository**:

2. **Setup Development Environment**:
- **Arduino IDE**: Install the ESP32 board support through the Board Manager.

3. **Configure Project:
- Update the **main.h** file with your specific settings such as Wi-Fi credentials and sensor configurations.

4. **Install Libraries**:
- Run script.bat located in _Source Files_.

4. **Build and Flash**:
- Open the sow_fw.ino file and click on the upload button.

## Author

Alejandro Gutierrez

## Change Log

All notable changes to this project will be documented in the CHANGELOG.md file.