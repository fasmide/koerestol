var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');

var routes = require('./routes/index');
var users = require('./routes/users');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

// uncomment after placing your favicon in /public
//app.use(favicon(__dirname + '/public/favicon.ico'));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use(express.static(path.join(__dirname, 'bower_components')));

app.use('/', routes);
app.use('/users', users);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
    var err = new Error('Not Found');
    err.status = 404;
    next(err);
});

var WebSocketServer = require('ws').Server
  , wss = new WebSocketServer({ port: 3001 });
 
wss.on('connection', function connection(ws) {
  ws.on('message', function incoming(message) {
    var data = JSON.parse(message);
    console.log("writing, ", data.x.toFixed(0), data.y.toFixed(0))
    buf.writeInt8(parseInt(data.y, 10), 3);
    buf.writeInt8(parseInt(data.x, 10), 4);
    buf[5] = checksum(buf);
    console.log(buf, data);
  }); 
});

var SerialPort = require("serialport").SerialPort,
        debug = require('debug')('Stol');

var serialPort = new SerialPort("/dev/ttyACM0", {
  baudrate: 115200
});

//[74, 0, 0, x, y, checksum];
var buf = new Buffer([74, 0, 0, 0, 0, 181]);

serialPort.on('open', function() {
    debug("Serial open");
    setInterval(function() {
            serialPort.write(buf);
            debug("TX:", buf);
    }, 10);
    serialPort.on('data', function(d) {
            debug("RX:", d);
    });
});

function checksum(arr) {
    var sum = 255;
    for (var i = 0; i <= 4; i++) {
        sum -= arr[i];
        if(sum <= 0) {
            sum += 256;
        }
    }
    return sum;
}



// error handlers

// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
    app.use(function(err, req, res, next) {
        res.status(err.status || 500);
        res.render('error', {
            message: err.message,
            error: err
        });
    });
}

// production error handler
// no stacktraces leaked to user
app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
        message: err.message,
        error: {}
    });
});


module.exports = app;
