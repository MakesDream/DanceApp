# DanceApp

DanceApp is a small GUI program designed to be ran on a computer to configure and save FSR threshold values to Arduino Leonardo based Stepmania Controllers. it will not work with Arduino Uno or other arduinos that do not support USB HID.

Rather than run complicated web apps or require extra software be installed on the computer, DanceApp utilizes the COM port already connecting an arduino based controller to the Clients PC. It does this in a lightweight manner and uses few resources and minimal disk space. Furthermore since it supports saving values to the Arduino based controller, DanceApp should not need be ran often, and only needs to be accessed to make infrequent changes to the configuration.

Included is the Excecutable itself, and an example arduino file to show how I implemented arduino compliance with DanceApp. You can use the example file as a reference or install it directly to your controller, just make sure to configure the analog inputs so they point to the right FSRs in your design. the example file DOES NOT support addressable RGB LEDs at this time, it does support small LEDs on the board to quickly indicate if the currently defined thresholds for each sensor is currently being met.

# How to use DanceApp

DanceApp connects to the Arduino based controller over the COM port, so the first step to using it is to manually select the COM port the Arduino controller is located at. once you select a port, it will attempt to open the port, if successful, and the arduino controller is present, it should start displaying live readings of your FSRs in the bars corresponding to each sensor.

default values are 400/1023 for each sensor. to adjust the thresholds either click and drag the handles on the sliders, enter a value into the spin control to the right of the sliders, or click the up and down arrows on the spin controls. If you want a sensor to be more sensitive and easier to trigger, lower the threshold value. If you want it to be less sensitive and harder to trigger, increase the threshold value.

once you have the values set where you want them, pressing the "OK" button will send the values to the board and update the behavior of the Arduino based controller, however the new values will not be saved to the EEPROM unless the "Apply" button is pressed. Pressing the "Reset" Button will also not save new values to EEPROM but will simply reset the values in the UI to the default of 400 each.

# Limitations and Possible future upgrades

At this time DanceApp only supports Windows
At this time DanceApp only supports 4 panel Dance Controllers
At this time DanceApp only supports 4 FSRs per controller, or 1 sensor per panel
At this time DanceApp does not support addressable RGB LEDs
At this time DanceApp can not automatically detect compatible controllers and has to be manually pointed to an appropriate COM port


