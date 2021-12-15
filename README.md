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
![image](https://user-images.githubusercontent.com/35699948/146280671-ec8f25ad-a83f-4d4c-a465-655dc6fb187f.png)
This program was created for use in Intro to Embedded Systems at Rowan University as a Final Project
