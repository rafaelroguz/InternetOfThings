const MongoClient = require('mongodb').MongoClient;
const uri = "mongodb+srv://rafael:S7BNKu4WAj2z3ca6@nonstructureddatamanagementclass-xa2lb.mongodb.net?retryWrites=true";
const client = new MongoClient(uri, { useNewUrlParser: true });

var express = require('express');
var app = express();
var server = app.listen(8000, () => { //Start the server, listening on port 8000.
    console.log("Listening to requests on port 8000...");
})
var io = require('socket.io')(server); //Bind socket.io to our express server.

app.use(express.static('public')); //Send index.html page on GET /
io.on('connection', (socket) => {
    console.log("Someone connected."); //show a log as a new client connects.
})

client.connect(err => {
    if (err) throw err;
    
    const collection = client.db("IoT").collection("temperatura");

    /*collection.findOne({}, function(err, result) {
        if (err) throw err;
        io.sockets.emit("temp", {date: result.date.day + "-" + result.date.month + "-" + result.date.year, time: (result.time.hours + ":" + result.time.minutes), temp: result.temp}); //emit the datd i.e. {date, time, temp} to all the connected clients.
        console.log(result);
    });*/

    while (true) {
        console.log("while");
        collection.find({}).toArray(function(err, result) {
            if (err) throw err;
            console.log(result);
        });
        sleep(5000);
    }
    /*do {
        collection.findOne({}, function(err, result) {
            if (err) throw err;
            io.sockets.emit("temp", {date: result.date.day + "-" + result.date.month + "-" + result.date.year, time: (result.time.hours + ":" + result.time.minutes), temp: result.temp}); //emit the datd i.e. {date, time, temp} to all the connected clients.
            console.log(result);
        });
        sleep(1000);
    } while (true);*/
});

function sleep(milliseconds) {
    var start = new Date().getTime();
    for (var i = 0; i < 1e7; i++) {
    if ((new Date().getTime() - start) > milliseconds){
        break;
    }
    }
}

