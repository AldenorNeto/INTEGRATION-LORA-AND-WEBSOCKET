const char script[] PROGMEM =
R"=====(
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
    document.getElementById('duracao'+INDICE).value = jsonEsp.D
    document.getElementById('timeSemana'+INDICE).value = jsonEsp.H
                
    for(let ind in jsonEsp.S){
        document.getElementById('S'+INDICE+'_'+ind).checked = parseInt(jsonEsp.S[ind])
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
                document.getElementById('umidade'+ino).innerHTML = jsonEsp.U.substring(1);
                document.getElementById('bomba'+ino).checked = parseInt(jsonEsp.B);
            }
        }
    }

  },500);

  var isOpen = ws => ws.readyState === ws.OPEN 

  function fanONOFF(){   
    for(let index = 1; index < 6; index++) {
        websock.send('DURACAO'+index+'=' + String(document.getElementById('duracao'+index).value));
        websock.send('HORA'+index+'=' + String(document.getElementById('timeSemana'+index).value));
        let vetor = []
        for(let ino in jsonEsp.S){
            if(document.getElementById('S'+index+'_'+ino).checked)vetor +='1';
            else vetor +='0';
        }
        websock.send('S'+index+'='+vetor);
    }
  }

</script>
</html>
)====="; 
