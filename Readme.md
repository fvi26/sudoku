<div align="center">

# SUDOKU

</div>
Sudoku is a logic-based puzzle game where the player fills a 9x9 grid with numbers 1 through 9. The goal is to ensure that no number repeats in any row, column, or 3x3 subgrid. This project brings Sudoku into an interactive format using an Arduino-based hardware setup. The player inputs numbers via a 4x4 keypad and views the game on an LCD screen, creating an engaging embedded systems experience.
# Introduction

This project is a simple interactive puzzle game where the player solves Sudoku by entering numbers via a keypad. The game is displayed on a TFT LCD screen, and the hardware is managed by an Arduino microcontroller.
The purpose of this project is to deepen knowledge about embedded programming by implementing a real-world application. I chose Sudoku because it offers both a mental challenge and a fun way to learn about hardware and software integration. This project represents progress in my learning journey and an opportunity to implement concepts such as SPI communication and keypad input handling.
# General Description

The game begins by displaying a Sudoku puzzle on the TFT screen. The player uses a 4x4 keypad to navigate the grid and input numbers.
The program validates each move to ensure it complies with Sudoku rules.
Once the grid is completed correctly, a congratulatory message is displayed.
The player can restart the game to try another puzzle.

#### For this project, I will use various features from previous lab exercises:
   - Timers & Interrupts (Lab 2): Used to manage grid updates and user input validation.
   - Keypad Input (Lab 3): Processes number entries and directional controls for navigating the grid.
   -  SPI Communication (Lab 4): Handles data transfer between the Arduino and the TFT LCD.
     
# Hardware Design
#### General Description :
This project uses a 1.8" TFT LCD display with SPI protocol for displaying the Sudoku grid. A 4x4 keypad allows the user to input numbers and navigate the grid. The hardware setup is powered by an Arduino Uno and includes basic components like connecting wires, a breadboard, and resistors.

#### Component List : 
| Name                               | Source                   |
|------------------------------------|--------------------------|
| Arduino Uno                        | University Of Bucharest  |
| LCD display 1.8" with SPI and controller TFT ST7735                  | Optimusdigital      |                  
| Connecting Wires                   | University Of Bucharest  | 
| Breadboard                         | University Of Bucharest  |
| Keypad 4*4 with mother pins        | Optimusdigital           |

## Pins Configuration

### TFT Display Pinout and Connections:

| **Component**            | **Arduino Pin** | **Function Description**                                                      |
|--------------------------|-----------------|-------------------------------------------------------------------------------|
| **SCK (Clock)**           | Pin 13          | Clock signal for communication with the display (SCK for SPI)                 |
| **SDA (Data Input)**      | Pin 11          | Data input for the display (MOSI for SPI)                                    |
| **RES (Reset)**           | Pin 10          | Resets the display                                                           |
| **DC (Data/Command)**     | Pin 12          | Controls whether data or command is being sent (Data/Command)                |
| **CS (Chip Select)**      | Pin A0          | Activates the display for communication (Chip Select)                         |
| **BL (Backlight)**        | 3.3V (or GND with a resistor for PWM control) | Controls backlight brightness (via resistor or PWM control for brightness) |
| **VCC (Power)**           | 3.3V            | Power supply for the display (must be 3.3V to avoid damage)                   |
| **GND (Ground)**          | GND             | Ground connection                                                            |

### Keypad Pinout and Connections:

| **Component**            | **Arduino Pin** | **Function Description**                                                      |
|--------------------------|-----------------|-------------------------------------------------------------------------------|
| **Row 1**                | Pin 2           | Row 1 of the keypad                                                          |
| **Row 2**                | Pin 3           | Row 2 of the keypad                                                          |
| **Row 3**                | Pin 4           | Row 3 of the keypad                                                          |
| **Row 4**                | Pin 5           | Row 4 of the keypad                                                          |
| **Column 1**             | Pin 6           | Column 1 of the keypad                                                       |
| **Column 2**             | Pin 7           | Column 2 of the keypad                                                       |
| **Column 3**             | Pin 8           | Column 3 of the keypad                                                       |
| **Column 4**             | Pin 9           | Column 4 of the keypad                                                       |

### Block diagram
![Diagramă fără titlu drawio](https://github.com/user-attachments/assets/dee32cf2-ad08-4ef8-ac74-d7f645f0a72a)



# Software Design
For this project, I am using PlatformIO as the development environment.
# Results
# Conclusions
