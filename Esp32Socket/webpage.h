String webpageCont PROGMEM (){
return R"=====(
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>IRRIGAÇÃO</title>
    
</head>
<body onselectstart="return false">
    <div class="container">
        <h1><span>Grendene</span>IRRIGAÇÃO 4.0<div><i class="gg-drop-invert"></i></div></h1>
       
        <button id="envioForm" onclick="fanONOFF()">✓</button><div id="farofa"></div>
        <TABLE>
            <tr id="cabecalho">
                <td>LOCAL</td>
                <td>MINUTOS</td>
                <td>HORARIO</td>
                <td>DIA</td>
                <td>UMIDADE</td>
                <td>IRRIGAR</td>
            </tr>

        <tr>
                <td class="titulo">Fab 01</td>
                <td><select class="duracao">
                    <option value="1">5:00</option>
                    <option value="2">10:00</option>
                    <option value="3">15:00</option>
                    <option value="4">20:00</option>
                    <option value="5">25:00</option>
                </select></td>
                <td><input type="time" class="timeSemana"></div></td>
                <td><div class="DATA">
                    <div class="semana">
                        <label>
                            <input type="checkbox" class="S0"><div class="dom">D</div>
                        </label>
                        <label>
                            <input type="checkbox" class="S1"><div class="seg">S</div>
                        </label>
                        <label>
                            <input type="checkbox" class="S2"><div class="ter">T</div>
                        </label>
                        <label>
                            <input type="checkbox" class="S3"><div class="qua">Q</div>
                        </label>
                    </div>
                    <div  class="semana">
                        <label>
                            <input type="checkbox" class="S4"><div class="qui">Q</div>
                        </label><label>
                            <input type="checkbox" class="S5"><div class="sex">S</div>
                        </label><label>
                            <input type="checkbox" class="S6"><div class="sab">S</div>
                        </label>
                    </div>
                </div></div>
                </td>
                <td><div class="umidade"><span class="umidad">0</span>%</div></td>
                <td><label class="estadoBomba">
                    <input type="checkbox" class="bomba"><div></div>
                </label></td>
        </tr>

    <style>
      #cabecalho td{background-color:#bdf0ff;padding:5px 5px;height:150%;max-width:min-content;font-size:calc(1vw + 5px)}#containerButton{display:flex;justify-content:space-between;position:absolute;width:96%;left:2%;bottom:10px;align-self:start}option{background-color:#00000036}button{position:absolute;left:10px;bottom:10px;color:#fff;font-size:30px;width:50px;height:50px;border-radius:50%;margin:5px}.duracao{width:100%;height:100%;border:none}#envioForm{background-image:linear-gradient(to bottom right,#0f0 50%,#00c900 50%);font-weight:700}#containerButton #cancel{background-image:linear-gradient(to bottom right,red 50%,#c70000 50%)}table{position:relative;margin:10px;justify-content:center;background-color:#fff;align-items:center;border-collapse:collapse;font-family:'Trebuchet MS';width:90%;max-width:1500px}td{border:2px solid #727272;text-align-last:center;align-items:center;justify-content:center;height:50px;width:min-content;max-width:15em;width:min-content}.container{display:flex;min-width:calc(90% + 70px);display:flex;flex-direction:column;justify-content:center;align-items:center}#conteiner_relogio{height:min-content;width:100%}#farofa{position:absolute;background-color:#daf6ff60;top:10%;width:100%;height:80%;z-index:10}.estadoBomba input+div,.umidade{font-size:calc(2.7vw + 10px);padding:0 4px}.titulo,input[type=time],select{font-size:calc(2.6vw + 5px);white-space:nowrap;text-overflow:ellipsis;overflow:hidden!important}body{display:flex;flex-direction:column;align-items:center;background-attachment:fixed;text-align-last:center;background-image:linear-gradient(#daf6ff 85%,#afffa1);min-height:90%;justify-content:center;cursor:context-menu;border:3px double #afffa107}h1{display:flex;flex-direction:row;justify-content:center;align-items:end;color:#008b8b;font-size:calc(2.3vw + 7px);font-family:cursive;margin-top:-5px}h1 span{color:#00008b;font-size:calc(2.3vw + 12px);font-family:Verdana;margin-bottom:10px;margin-right:10px}h1 div{display:flex;align-items:center;margin:5px;color:#19d700;margin-bottom:12px}.gg-drop-invert{box-sizing:border-box;position:absolute;display:block;transform:rotate(70deg) scale(var(--ggs,1));width:calc(2vw + 10px);height:calc(2vw + 10px);max-width:32px;max-height:32px;border-radius:0 100% 100% 100%;box-shadow:inset 0 0 0 5px;overflow:hidden}.gg-drop-invert::before{content:"";display:block;position:absolute;box-sizing:border-box;width:calc(1.4vw + 10px);height:calc(1.5vw + 10px);background:currentColor;transform:rotate(-65deg);border-radius:50px 30px;right:0;top:-5px}#estadoIrrigar{width:100%;height:100%;background-color:#ced2ff;padding:0}select{height:60px}input[type=checkbox]{display:none}input[type=time]{border:none;appearance:auto;width:100%;height:100%;padding:2px 2px;cursor:text;background-color:#ffffff00}input[type=time]:hover{background-color:#bfbfbf50}.estadoBomba input+div{display:flex;padding:0 4px;background-color:#c2c2c2;height:100%;justify-content:center;align-items:center;cursor:pointer}.estadoBomba input:checked+div{background-color:#09ff00}.estadoBomba input+div:hover{background-color:#afafaf}.estadoBomba input+div::after{content:"OFF"}.estadoBomba input:checked+div:hover{background-color:#51ff4b}.estadoBomba input:checked+div::after{content:"ON"}@media screen and (min-width:600px){.dom::after{content:"OM"}.seg::after{content:"EG"}.ter::after{content:"ER"}.qua::after{content:"UA"}.qui::after{content:"UI"}.sex::after{content:"EX"}.sab::after{content:"AB"}}.semana label input+div{display:flex;justify-content:center;align-items:center;background-color:#ddd;font-size:calc(1vw + 5px);height:min-content;max-height:18px;border:1px solid;margin:0 calc(.1vw + .5px);padding:4% calc(.5vw)}.semana label input+div:hover{background-color:#d0d0d0}.semana label input:checked+div{font-weight:700;background-color:#ffe600}.semana{display:flex;justify-content:space-around;height:max-content;width:min-content;align-items:center;margin:1px 0}.DATA{display:flex;height:80%;width:100%;position:relative;flex-direction:column;align-items:center;justify-content:space-around}.DATA:hover{background-color:#fbff0018}.irrigar{display:flex;width:100%}.relogio{display:flex;border:1px solid;align-items:end;flex-direction:row;font-family:monospace;font-weight:700;padding:3px 3px;background-color:#fff;margin:10px;margin-top:30px;margin-bottom:30px;float:right}.relogio div span{font-size:calc( 1vw + 10px);background-color:#ff0;border:1px solid;padding:5px 10px;margin:3px}.relogio div{display:flex}td span:hover{background-color:#00000003}.titulo:hover{background-color:#53535314}.titulo+div{display:flex;opacity:0;position:absolute;font-size:0px;left:470px;background-color:#fff67ce6;border:solid 0;padding:0}table input{border:none;width:100%;height:100%}
    </style>
        </TABLE>
        <div id="conteiner_relogio">
            <div><div class="relogio">
                <div id="relogioD">Carregando...</div>
                <div id="relogioH"></div>
                <div id="relogioS"></div>
            </div></div>
        </div>
    </div>

</body>

<script>

  const mostraTime = () => {
    var nD = new Date();
    var dia = nD.getDate();
    var mes = (nD.getMonth() + 1);
    var ano = nD.getFullYear();
    var hora = nD.getHours();
    var minuto = nD.getMinutes();
    var semana = nD.getDay();
    
    if(dia < 10)dia = "0" + dia;
    if(mes < 10)mes = "0" + mes;
    if(hora < 10)hora = "0" + hora;
    if(minuto < 10)minuto = "0" + minuto;
    
    if(semana == 0)StrigSemana = "Domingo";
    else if(semana == 1)StrigSemana = "Segunda";
    else if(semana == 2)StrigSemana = "Terça";
    else if(semana == 3)StrigSemana = "Quarta";
    else if(semana == 4)StrigSemana = "Quinta";
    else if(semana == 5)StrigSemana = "Sexta";
    else if(semana == 6)StrigSemana = "Sabado";
    
    document.getElementById("relogioD").innerHTML = ("<span> "+dia+"/"+mes+"/"+ano+" </span>");
    document.getElementById("relogioH").innerHTML = ("<span> "+hora+":"+minuto+" </span>");
    document.getElementById("relogioS").innerHTML = ("<span> "+StrigSemana+" </span>");
  }
  //console.log(window.location.hostname);
  mostraTime();
  setInterval(mostraTime,10000);

  var json = 0
  let firtScanf = 0;
  InitWebSocket()
  function InitWebSocket(){
    websock = new WebSocket('ws://'+window.location.hostname+':81/');
    websock.onmessage = jsonMaster => {
        jsonEsp = JSON.parse(jsonMaster.data);
        document.getElementById('farofa').style.display='none'
        json = 0
        if(firtScanf < 10){
            setupTabela(jsonEsp.I)
            firtScanf++;
        }
    }
  }
    
    var setupTabela = INDICE => {
        document.querySelectorAll('.duracao')[INDICE-1].value = jsonEsp.D
        document.querySelectorAll('.timeSemana')[INDICE-1].value = jsonEsp.H
        for(let ind in jsonEsp.S){
            document.querySelectorAll('.S'+ind)[INDICE-1].checked = parseInt(jsonEsp.S[ind])
        }
    }

  //setTimeout(setVariaveisPag,1000)
  var socketOk = false
  setInterval(() => {
    json++
    console.log(json);
    if(isOpen(websock)) socketOk = true 
    if(json > 50){
        console.log("-=-=-=-=-=-=-=");
        location.reload();
        json = 0;
    };
    if(socketOk && firtScanf){
        for(let ino = 0; ino < 7; ino++){
            if(jsonEsp.I == ino){
                document.querySelectorAll('.umidad')[ino-1].innerHTML = jsonEsp.U.substring(1);
                document.querySelectorAll('.bomba')[ino-1].checked = parseInt(jsonEsp.B);
            }
        }
    }

  },500);

  var isOpen = ws => ws.readyState === ws.OPEN 

  function fanONOFF(){   
    for(let index = 1; index < 6; index++) {
        websock.send('DURACAO'+index+'=' + String(document.querySelectorAll('.duracao')[index-1].value));
        websock.send('HORA'+index+'=' + String(document.querySelectorAll('.timeSemana')[index-1].value));
        let vetor = []
        for(let ino in jsonEsp.S){
            if(document.querySelectorAll('.S'+ino)[index-1].checked)vetor +='1';
            else vetor +='0';
        }
        websock.send('S'+index+'='+vetor);
    }
  }

</script>
</html>
)====="; }
