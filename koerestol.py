import serial
import sys

ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
import numpy as np
import matplotlib.pyplot as plt

plt.axis([0, 255, 0, 255])
plt.ion()
plt.show()

while True: 
	if ord(ser.read()) == 74:
			x = False
			y = False
			for i in xrange(0, 10):
				if i is 2:
					x = ord(ser.read())
					sys.stdout.write(str(x))
					sys.stdout.write("\t")
					continue	
				if i is 3:
					y = ord(ser.read())
					sys.stdout.write(str(y))
					sys.stdout.write("\t")
					continue
				if x and y:
					plt.scatter(x, y)
					plt.draw()
				sys.stdout.write(str(ord(ser.read())))
				sys.stdout.write("\t")

			print(" ")
