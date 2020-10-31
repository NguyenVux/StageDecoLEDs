"use strict";
const { randomInt } = require('crypto');
let express = require('express');
let app = express();
let http = require('http').createServer(app);
let io = require('socket.io')(http);
let fs = require('fs');



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
  console.log(ledCount);
})();


for(let i = 0; i < ledCount ; ++i)
{
  LedsInfo.push(Color(randomInt(0,255),randomInt(0,255),randomInt(0,255)));
}

io.on('connection', (socket) => {
  console.log(LedsInfo);
  io.emit('init',LedsInfo);
  socket.on('update',()=>{
    console.log("Recive on update");
    for(let i = 0; i < ledCount ; ++i)
    {
        LedsInfo[i] = Color(randomInt(0,255),randomInt(0,255),randomInt(0,255));
    }
    io.emit('update',LedsInfo);
  });
});



http.listen(3000, () => {
  console.log('listening on port: 3000');
});