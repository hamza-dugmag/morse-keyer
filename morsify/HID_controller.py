# https://stackoverflow.com/questions/52460149/keyboard-not-found-even-though-im-including-keyboard-h
# https://raspberrypi.stackexchange.com/questions/74742/python-serial-serial-module-not-found-error

import serial
import keyboard
from datetime import datetime

# Connect to Arduino
port = "COM3"
baud = 9600
arduino_serial = serial.Serial(port, baud)

# Confirmation message
dt = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
print("STARTED READING " + str(port) + " (BAUD=" + str(baud) + ") ON " + str(dt))

while True:
    # Read serial and output keypress
    incoming_data = str(arduino_serial.readline())
    keyboard.write(incoming_data[2])
    incoming_data = ""
