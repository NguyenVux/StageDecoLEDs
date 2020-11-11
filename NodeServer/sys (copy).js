'use strict';

const epxress = require('express');
let app = epxress();

app.get('/',(req,res)=>{

    res.send("HELLO WORLD");
});
app.listen(80);
