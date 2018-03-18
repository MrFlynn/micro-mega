# µMega
Demo kernel and operating system written for ATmega 1284 written for my final
project in CS120B at UC Riverside (Winter 2018). This project employs a state
machine driven design, as per the design goals of the course.

Outside of required classwork, this project has these additional goals:
1. Designing a complex and functional embedded system.
2. Further understanding the design of embedded and real-time operating systems.
3. Try my hand at designing a functional filesystem.

## Installation:
If you wish to test this project out for yourself, you must have `avr-gcc` installed to compile the project. Additionally, you will need a project like [Atmel Studio](https://www.microchip.com/avr-support/atmel-studio-7) or [AVRDUDE](https://www.nongnu.org/avrdude/) to upload your code to the micro-controller.

## Hardware:
Below is a list of hardware you will need to construct this system.
* ATmega 1284
* 5 Vdc PSU
* Lumex Optoelectronics LCM-SO1602DTR/M
* PS/2 Breakout Cable

## Schematics
Included in this repository (under the `schematics/` folder) is a Fritzing schematic that shows how to connect all the circuit elements together. If you don’t have Fritzing installed, a vector graphics image is also included that shows how to connect everything on a breadboard.
