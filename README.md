README for Microphone-Controlled-Servo-on-MSP430


________________________________________________________________________________________________________

Author: Kyle Rettig 
Created: December 15, 2021 
Latest Update: Initial Commit
________________________________________________________________________________________________________
Description: Uses an electret condenser microphone to control a servo with the MSP430G2553's ADC and PWM
________________________________________________________________________________________________________
FILES REQUIRED: msp430.h

VARIABLES USED: rawMic, i

PROGRAM FUNCTIONS: Uses an electret condenser microphone to control a servo with the MSP430G2553's ADC and PWM. Includes an RGB output to recognize noise level, as well as a button interrupt to set custom servo speed on button press.
