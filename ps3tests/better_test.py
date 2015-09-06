from evdev import InputDevice, list_devices, categorize, ecodes

devices = [InputDevice(fn) for fn in list_devices()]

for dev in devices:
	print(dev.fn, dev.name, dev.phys)

index = int(raw_input('Choose index: ') or 0)

codes_we_dont_want_to_see = [4, 5, 6]; #These are accelerometer

for event in devices[index].read_loop():
	if event.code == 0 and event.type == 0 and event.value == 0:
		continue

	if event.code not in codes_we_dont_want_to_see:
		print(event)
