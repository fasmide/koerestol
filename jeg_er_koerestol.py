import serial
import sys
import struct
from time import sleep


ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)

count = 0
while True:
	while count < 1000:
		ser.write(bytearray([74, 0, 0, 2, 0, 179]))
		ser.flush()
		count +=1
		while ser.inWaiting():
			print struct.unpack('B', ser.read())
	
		sleep(0.010)
	count = 0
	while count < 1000:
		ser.write(bytearray([74, 0, 0, 22, 0, 159]))
		ser.flush()
		count += 1
		while ser.inWaiting():
			print struct.unpack('B', ser.read())
	
	sleep(0.010)