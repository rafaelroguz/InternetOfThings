var express = require('express');
var app = express();
var server = app.listen(8000, () => { //Start the server, listening on port 8000.
    console.log("Listening to requests on port 8000...");
})

var io = require('socket.io')(server); //Bind socket.io to our express server.

app.use(express.static('public')); //Send index.html page on GET /

const SerialPort = require('serialport'); 
const Readline = SerialPort.parsers.Readline;
const port = new SerialPort('COM8'); //Connect serial port to port COM7. IDE -> Tools -> Port. COM7 is for bluetooth
const parser = port.pipe(new Readline({delimiter: '\r\n'})); //Read the line only when new line comes.

parser.on('data', (temp) => { //Read data
    console.log(temp);
    var today = new Date();
    io.sockets.emit('temp', {date: today.getDate()+"-"+today.getMonth()+1+"-"+today.getFullYear(), time: (today.getHours())+":"+(today.getMinutes()), temp:temp}); //emit the datd i.e. {date, time, temp} to all the connected clients.
});

io.on('connection', (socket) => {
    console.log("Someone connected."); //show a log as a new client connects.
})