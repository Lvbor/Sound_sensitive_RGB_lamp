# Sound-Sensitive RGB Lamp
This repository contains the source code and documentation for building a sound-reactive RGB lamp using the ESP32 Wemos D1 R32 board, WS2812B RGB LED strip, and DFRobot DFR0034 microphone module.

## Introduction
A sound-sensitive RGB lamp is an electronic device that reacts to sound by changing its color. The goal of this project is to create an ambient light source for homes that enhances the environment and adds an extra level of interactivity and excitement through sound-reactive technology.

## Technologies Used

### Languages
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
### Tools and others
![FastLED](https://img.shields.io/badge/fastled-870099?style=for-the-badge) ![VSCode](https://img.shields.io/badge/VSCode-007ACC?style=for-the-badge)  ![Git](https://img.shields.io/badge/git-%23FF0000.svg?style=for-the-badge&logo=git&logoColor=white) ![PlatformIO](https://img.shields.io/badge/PlatformIO-ebab34?style=for-the-badge)
### Boards
![ESP32](https://img.shields.io/badge/esp32-000000?style=for-the-badge)
### OS
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white) 

## Features
* 13 RGB effects (2 sound-reactive)
* Customizable effects
* Temperature, pressure, altitude and humidity measurement
* Built-in microphone


## Hardware Components
The following hardware components are used to build the sound-reactive RGB lamp:

* [ESP32 Wemos D1 R32 board](https://pl.aliexpress.com/item/33052923558.html)
* [WS2812B RGB LED strip](https://www.aliexpress.com/item/1005005197418171.html)
* [DFRobot DFR0034](https://www.tme.eu/pl/details/df-dfr0034)
* [5V DC power supply](https://www.aliexpress.com/item/4000594896227.html)
* [BME280 sensor](https://www.aliexpress.com/item/1005003622447376.html)
* [SSD1306 OLED display](https://www.aliexpress.com/item/1005004355547926.html)

## Software
The software required for building the sound-reactive RGB lamp involves programming the ESP32 Wemos D1 R32 board. The programming language used for the ESP32 board is C++.

The full code can be found in the project files.

## Installation
To install and run this project on your ESP32 board, follow these steps:

1. Clone or download this repository to your local machine.
2. Open the project in your preferred Integrated Development Environment (IDE) that supports ESP32 development. (I used VS Code)
3. Connect the ESP32 board to your computer via USB.
4. Configure the IDE to use the appropriate board and port settings for the ESP32.
5. Compile and upload the code to the ESP32 board.
6. Once the code is uploaded, disconnect the board from the computer and connect the hardware components.
7. Power on the sound-reactive RGB lamp and enjoy the ambient lighting experience!

## Gallery

[Click here](https://github.com/Lvbor/Sound_sensitive_RGB_lamp/wiki)

## License
This project is licensed under the MIT License. Feel free to modify and distribute the code as per the terms of the license.

## References and Resources

* [FastLED documentation](https://github.com/FastLED/FastLED/wiki/Overview)
* [Adafruit SSD1306 documentation](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)
* [BME280 datasheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme280-ds002.pdf)
* [DFR0034 documentation](https://wiki.dfrobot.com/Analog_Sound_Sensor_SKU__DFR0034)
* [Wemos D1 R32 documentation](https://www.halloweenfreak.de/arduino/pdfs/D1_R32_ENG.pdf)




