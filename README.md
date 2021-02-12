# Attiny13A_Laser_Trapwire
An optimized little project for a demanding tiny microcontroller.

## Introduction

Just got an Attiny13A for challenging myself to work some skills on optimizing code and power cosumption in my projects. The first project I thought was a laser trapwire.

The idea is simple: a laser module gets it's light recepted by a LDR photoresistor. If someone crosses the laser line, the system activates a notification buzzer.

## Some Remarks

-I used an Arduino Mega to burn the Attiny13A's bootloader and to program it via ISP;
-I'm using the following json: https://raw.githubusercontent.com/sleemanj/optiboot/master/dists/package_gogo_diy_attiny_index.json, in Files->Preferences, in the Aditional Boards Manager URLs. I'm using it's the 'DIY Attiny' core.

## Hardware Choices

At a first glance, one can think about constantly reading the analog signal from the LDR using an ADC capable pin and activating the buzzer if the signal happens to change. There is a better solution for this: we can sleep the Attiny all the time and wake it up when the laser line is interrupted. So we need to use the LDR signal as an external interrupt in our sketch.

Yeah I know, the LDR signal is analog and for an external interrupt we expect a digital signal. But for our little microcontroller friend, any voltage above 3V is seen as logical HIGH and any voltage below 2V is understood as logical LOW. For our practical porposes, when the laser is interrupted, our Attiny will understand an external interruption on the right pin (PB1, according the datasheet).

## Optimizing Power Consumption

There are some development decisions that can improve our system's power consuption, such as:
-Setting our processor speed to 1.2MHz and overriding the frequency to 128KHz (For programming your attiny uisng 128KHz clock you will need the special Arduino Slow ISP code provided here: https://forum.arduino.cc/index.php?topic=89781.330. Just upload it to your Arduino and change the MOSI/MISO/SCK/RESET pins if you're not using the Uno board.);
-Using a method equivalent to Attiny85's 'power_all_disable();' and closing the BOD CONTROL Register;
-Disabling both ADC and analog comparator.

## Optimizing the Code

As for our code, we can optimize it burning the smallest bootloader that we need, and in that case we can choose the simplest settings:
-No millis, No tone (without tone, buzzer will be activated with a simple digitalWrite());
-Millis accuracy better or equal 50% error;
-Print support bin only;
-Serial support: Serial duplex: read+write;
-LTO enabled;
-Brown out detection level 2.7V;
-Override clock source internal 128KHz;
-Override frequency 128KHz.
Last but not least, we can also get some code optimization from commands using port manipulations.

## Results

"Sketch uses 166 bytes (16%) of program storage space. Maximum is 1024 bytes.
Global variables use 1 bytes (1%) of dynamic memory, leaving 63 bytes for local variables. Maximum is 64 bytes."
