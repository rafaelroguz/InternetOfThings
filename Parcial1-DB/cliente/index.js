
const MongoClient = require('mongodb').MongoClient;
//const uri = "mongodb+srv://rafael:S7BNKu4WAj2z3ca6@nonstructureddatamanagementclass-xa2lb.mongodb.net?retryWrites=true";
const uri = "mongodb://localhost:27017/";
const client = new MongoClient(uri, { useNewUrlParser: true });

client.connect(err => {
    if (err) throw err;

    const collection = client.db("IoT").collection("temperatura");
    const SerialPort = require('serialport'); 
    const Readline = SerialPort.parsers.Readline;
    const port = new SerialPort('COM8'); //Connect serial port to port COM7. IDE -> Tools -> Port. COM7 is for bluetooth
    const parser = port.pipe(new Readline({delimiter: '\r\n'})); //Read the line only when new line comes.
  
    parser.on('data', (temp) => { //Read data
        var today = new Date();
        var data = {
          temperature: temp,
          date: {
              day: today.getDate(),
              month: today.getMonth()+1,
              year: today.getFullYear()
          },
          time: {
              hours: today.getHours(),
              minutes: today.getMinutes(),
              seconds: today.getSeconds()
          }
        }

        collection.insertOne(data, function(err, res) {
            if (err) throw err;
            console.log(data);
        });
    });

    //client.close();
});

