EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:teensy_3.1
LIBS:freetronics_schematic
LIBS:room-service-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Teensy_3.1 U?
U 1 1 57CD74FF
P 5700 3750
F 0 "U?" H 5750 4800 60  0000 C CNN
F 1 "Teensy-LC" H 5800 5250 60  0000 C CNN
F 2 "" H 5800 3750 60  0000 C CNN
F 3 "" H 5800 3750 60  0000 C CNN
	1    5700 3750
	1    0    0    -1  
$EndComp
Text Notes 6850 3650 0    60   ~ 0
SDA
Text Notes 6850 3500 0    60   ~ 0
SCL\n
$Comp
L R R?
U 1 1 57CD75BC
P 7400 3150
F 0 "R?" V 7480 3150 50  0000 C CNN
F 1 "2K6" V 7400 3150 50  0000 C CNN
F 2 "" V 7330 3150 50  0000 C CNN
F 3 "" H 7400 3150 50  0000 C CNN
	1    7400 3150
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 57CD75E3
P 7700 3150
F 0 "R?" V 7780 3150 50  0000 C CNN
F 1 "2K6" V 7700 3150 50  0000 C CNN
F 2 "" V 7630 3150 50  0000 C CNN
F 3 "" H 7700 3150 50  0000 C CNN
	1    7700 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3650 8150 3650
Wire Wire Line
	6700 3500 8150 3500
Wire Wire Line
	7400 3300 7400 3500
Connection ~ 7400 3500
Wire Wire Line
	7700 3300 7700 3650
Connection ~ 7700 3650
Wire Wire Line
	6700 2750 7700 2750
Wire Wire Line
	7400 2750 7400 3000
Wire Wire Line
	7700 2750 7700 3000
Connection ~ 7400 2750
Text Notes 8200 3600 0    60   ~ 0
16x2 Display
Text Notes 7900 3200 0    60   ~ 0
Pull-ups, apparently\nwe need these. :)
Text Notes 8250 3900 0    60   ~ 0
Also uses\n+5V, GND\n(not shown)\n
Text Notes 6750 4300 0    60   ~ 0
Latch
Text Notes 6750 4150 0    60   ~ 0
Clock
Text Notes 6750 4000 0    60   ~ 0
Data
Text Notes 7100 4250 0    60   ~ 0
TLC5947 pins
Text Notes 4100 4050 0    60   ~ 0
Pins 6-11\nTo Keypad\n
Wire Wire Line
	4700 3500 4250 3500
Wire Wire Line
	4250 3500 4250 3800
Wire Wire Line
	4700 4250 4250 4250
Wire Wire Line
	4250 4250 4250 4100
$EndSCHEMATC
