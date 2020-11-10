"use strict";
const { randomInt } = require('crypto');
const express = require('express');
const app = express();
const http = require('http').createServer(app);
const io = require('socket.io')(http);
const fs = require('fs');

const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
//const port = new SerialPort("COM3", { baudRate: 115200 });

//const parser = port.pipe(new Readline());

let preColor;
// parser.on('data', line => 
// {
  
//   if(line == true)
//   {
//     port.write(Buffer.from(preColor));
//     console.log("resend data");
//   }
//   else
//   {
//     console.log(`> ${line == true} - ${line}`);
//   }
  
// });


app.use(express.static('front_end'));



app.get('/', (req, res) => {
  res.sendFile('/index.html');
});

function Color(r,g,b)
{
    return {r:r,g:g,b:b};
}
let LedsInfo = [];
let ledCount = 0;

(()=>{
  let data =fs.readFileSync('./config.json','ascii');
  ledCount = JSON.parse(data).led_Count;
})();


for(let i = 0; i < ledCount ; ++i)
{
  LedsInfo.push(Color(randomInt(0,255),randomInt(0,255),randomInt(0,255)));
}

io.on('connection', (socket) => {
  io.emit('init',LedsInfo);
  socket.on('update',()=>{
    console.log("Recive on update");
    for(let i = 0; i < ledCount ; ++i)
    {
        LedsInfo[i] = Color(randomInt(0,255),randomInt(0,255),randomInt(0,255));
    }
    io.emit('update',LedsInfo);
  });

  socket.on("ColorChange",msg =>
  {
    preColor = Uint8Array.from(Object.values(msg));
    // port.write(Buffer.from(preColor));
    console.log("DATA SENDED");
  });
});



http.listen(3000, () => {
  console.log('listening on port: 3000');
});