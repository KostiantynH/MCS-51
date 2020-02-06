# MCS-51
programming of MCS-51 microcontroller (Keil + Proteus)

working with frequency: 
Get the UART frequency value and generate a 1/3 signal from the UART parameter. (
The frequency of the serial port - 4800 |
Shparnist pulses - 1/3 |
Output port - P1.6 |
Parameter accepted by UART - Frequency, kHz )

7-Segment Display:
Get arabic numbers on UART and display them on seven-segment indicators. (
The frequency of the serial port - 4800 |
The ports are connected to the indicator - 0, 1 |
Number of categories indicator - 5 |
Type Indicator - 7SEG-COM-AN-BLUE )

Keyboard:
Read the matrix keyboard, when pressed sends the serial number of the key pressed to the terminal via UART. Also show in binary code the sequence number of the key pressed on the LEDs. (
The frequency of the serial port - 4800 |
Matrix size keyboard - 4 * 5 |
Keyboard ports - 0, 1, 2, 3 )

