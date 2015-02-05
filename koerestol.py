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

			mereCheck = 255;
			mereCheck -= 74;

			for i in xrange(1, 6):
				value = ser.read()
				
				if i is 3:
					x = struct.unpack('b', value)[0]
				if i is 4:
					y = struct.unpack('b', value)[0]

				sys.stdout.write("%d: %d\t" % (i, ord(value)))

				if not i is 5: # we should not substract the checksum it self...
					mereCheck -= ord(value)
				if mereCheck <= 0:
					mereCheck += 256

			itr = itr + 1

			if itr % 15 is 1:			
				plt.scatter(x, y)
				plt.draw()
			print "sum: %d" % (mereCheck)
