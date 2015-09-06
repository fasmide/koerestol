from evdev import InputDevice, list_devices, categorize, ecodes

devices = [InputDevice(fn) for fn in list_devices()]

for dev in devices:
	print(dev.fn, dev.name, dev.phys)

index = int(raw_input('Choose index: ') or 0)

codes_we_dont_want_to_see = [0, 4, 5, 6];

for event in devices[index].read_loop():
	if event.code not in codes_we_dont_want_to_see:
		print(event)