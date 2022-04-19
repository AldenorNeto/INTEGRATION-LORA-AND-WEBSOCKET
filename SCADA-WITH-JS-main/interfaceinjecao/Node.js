const axios = require('axios');
const cheerio = require('cheerio');
const fs = require('fs');
const express = require('express');
const app = express();

app.get('/messages.json', (req, res) => {
    res.sendFile(__dirname+ "/messages.json")
  })

app.get('/', (req, res) => {
    res.sendFile(__dirname+ "/injetore.html")
  })

app.get('/style.css', (req, res) => {
    res.sendFile(__dirname + "/style.css")
  })

app.get('/remota.html', (req, res) => {
    res.sendFile(__dirname + "/remota.html")
})

app.get('/styleTempos.css', (req, res) => {
    res.sendFile(__dirname + "/styleTempos.css")
})

app.get('/scriptInt2.js', (req, res) => {
    res.sendFile(__dirname + "/scriptInt2.js")
  })

app.get('/jquery.js', (req, res) => {
    res.sendFile(__dirname + "/jquery.js")
  })

const PegaDados = async(url) => {
    const result = await axios.get(url)
    return result.data
}

/*const main = async () => {
    const content = await PegaDados("http://10.2.65.129/awp/index.html");
    const $ = cheerio.load(content);

    var numeno = $('#s3').text();

    console.log(numeno)
    let EscreveArquivo = () => {
        var messagesJson = JSON.stringify(numeno);        
        fs.writeFile("messages.json", messagesJson,err => {
            if (err) return console.log(err);
        });
    }
    EscreveArquivo();
}

setInterval(main,1000);*/

app.listen(8080)