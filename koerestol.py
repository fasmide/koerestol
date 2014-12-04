import serial
import sys
import struct
ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
import numpy as np
import matplotlib.pyplot as plt

plt.axis([-127, 127, -127, 127])
plt.ion()
plt.show()
itr = 0;
while True:
	
	if ord(ser.read()) == 74:
			x = False
			y = False
			for i in xrange(0, 10):
				if i is 2:
					x = struct.unpack('b', ser.read())[0]
#					x = ord(ser.read())
#					sys.stdout.write(str(x))
#					sys.stdout.write("\t")
					continue	
				if i is 3:
					y = struct.unpack('b', ser.read())[0]
#					y = ord(ser.read())
#					sys.stdout.write(str(y))
#					sys.stdout.write("\t")
					continue
				ser.read()
			sys.stdout.write("x: %s, y: %s" % (str(x), str(y)))
			itr = itr + 1
			if itr % 15 is 1:			
				print "draw! %d" % itr
				plt.scatter(x, y)
				plt.draw()

			print(" ")
