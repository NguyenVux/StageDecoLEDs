"use strict";



function toCSS(Color)
{
    if(Color.hasOwnProperty('r') &&Color.hasOwnProperty('g')&&Color.hasOwnProperty('b'))
    {
        return "rgb(" + Color.r + ", " + Color.g + ", " + Color.b + ")";
    }
}
let ledsInfo = [];
let ledsArrayUI = [];
let socket = io();

socket.on('init',(msg)=>{
    console.log(msg);
    for(let i = 0; i < msg.length; ++i)
    {
        let c = msg[i];
        ledsInfo.push(c);
    }
    for(let i = 0; i < ledsInfo.length; ++i)
    {
        let element = document.createElement("span");
        element.innerHTML = "led";
        element.className = "led";
        element.id = "Led:"+i;
        element.style.backgroundColor = toCSS(ledsInfo[i]);
        document.getElementById("led-container").appendChild(element);
        ledsArrayUI.push(element);
    }

});
    
socket.on('update',(msg)=>{
    if(msg.length - ledsInfo.length ===0)
    {
        msg.forEach((element,i) => {
            ledsInfo[i] = element;
            
        });
        ledsArrayUI.forEach((element,i) => {
            element.style.backgroundColor = toCSS(ledsInfo[i]);
        });
    }
    else{
        location.reload();
    }
});


