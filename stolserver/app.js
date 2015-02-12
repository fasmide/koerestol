var SerialPort = require("serialport").SerialPort,
	debug = require('debug')('Stol'),
	x = 0,
	y = 0;

var serialPort = new SerialPort("/dev/ttyACM0", {
  baudrate: 115200
});

serialPort.on('open', function() {
	debug("Serial open");
	setInterval(function() {
		var data = [74, 0, 0, x, y];
		data.push(checksum(data));
		serialPort.write(data);
		debug("TX:", data);
	}, 100);
	serialPort.on('data', function(d) {
		debug("RX:", d);
	});
});

function checksum(arr) {
	var sum = 255;
	arr.forEach(function(value) {
		sum -= value;
		if(sum <= 0) {
			sum += 256;
		}
	});
	return sum;
}

process.stdin.on('data', function(d) {
	var directions = d.toString().trim().split(',');

	x = parseInt(directions[0], 10);
	y = parseInt(directions[1], 10);
});