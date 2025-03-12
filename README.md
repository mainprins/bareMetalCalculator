# Calculator Project with ATmega328-1, LCD, and 4x3 Keypad
## Overview

This is a bare-metal project for a simple calculator built using the ATmega328-1 microcontroller, a 4x3 keypad, and an HD44780-2 LCD display. The calculator can perform basic arithmetic operations, including addition, subtraction, multiplication, and division. The project was designed as a learning exercise for interfacing with a keypad and LCD on the ATmega328-1 platform.
## Features

Basic arithmetic operations: Addition, Subtraction, Multiplication, Division
Clear button to reset the calculation
Simple user interface with a 4x3 keypad and LCD screen
Direct control over the LCD and keypad through low-level programming

## Components

Microcontroller: ATmega328-1
Keypad: 4x3 matrix keypad
LCD: HD44780-2 (Character LCD)
Power Supply: 5volt

## Pin Configuration
### Keypad Pinout

Rows (R1-R4) connected to: C0, C1, C2, C3
Columns (C1-C3) connected to: C4, C5, C6

### LCD Pinout

RS connected to: B0
RW connected to: B1
EN connected to: B2
Data pins (D0-D7) connected to: PORTD

## Setup Instructions

Hardware Setup:
    Connect the 4x3 keypad to the microcontroller according to the pin configuration above.
    Connect the HD44780-2 LCD to the microcontroller using the defined pinout.

Software Setup:
    Compile the code using your preferred toolchain for ATmega328-1.
    Flash the compiled code onto the microcontroller using an ISP programmer.

Operation:
    Upon powering the device, the LCD should display a ready prompt.
    Input numbers and operations using the keypad.
    The result will be displayed on the LCD.
