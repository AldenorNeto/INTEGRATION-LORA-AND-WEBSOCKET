//=====================
//HTML code for webpage
//=====================
const char webpageCont[] PROGMEM = 
R"=====(
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <title>IRRIGAÇÃO</title>
<body>

  <span id="Tempvalue">0</span> 
  
  <button id="FANbtn" onclick="fanONOFF()">OFF</button>
  <button id="faustao" onclick="fanONOFF()">OFF</button>

</body>
<script>
  InitWebSocket()
  function InitWebSocket(){
    websock = new WebSocket('ws://'+window.location.hostname+':81/');
    websock.onmessage = jsonMaster => {

      jsonEsp = JSON.parse(jsonMaster.data);
      console.log(jsonEsp);
      
      document.getElementById('Tempvalue').innerHTML = jsonEsp.TEMP;
      
      console.log( jsonEsp.LEDonoff[0]);
      
  
    }
  }

  function fanONOFF(){
    FANbtn = 'LEDonoff=ON';
    if(document.getElementById('FANbtn').innerHTML == 'ON'){
      FANbtn = 'LEDonoff=OFF';
    }
    websock.send(FANbtn);
  }

</script>
</html>
)=====";
