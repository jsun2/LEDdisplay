# LEDdisplay
Wireless 3 Digit LED display using NRF24L01

STL and inventor files for 3D models are included

The ino file works with all arduinos, using the NR24 Library together with a NRF24L01 chip.
The more powerful version of the wireless chip, with the antenna and extentions is also supported. Individual pin numbers are in the
comments section.

The digits all connect to a 74HC595 shift register. The common shift register can supply 80 mA for all 8 digits, which is usually
insufficient. A NPN transistor is recommended if you wire the 5mm LEDs in series for each segment to run them at the recommended 20 mA

Hardware used:
5mm LED
51k and 57 Ohm Resistors
2N NPN Transistors
9V Power supply
