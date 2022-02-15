//////MASTER
#include <LoRa.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <Wire.h>  
#include <FS.h>
#include <SPIFFS.h> 
#include "SSD1306.h"
#include "webpage.h"

SSD1306 display(0x3c, 4, 15, 0); //Cria e ajusta o Objeto display

const char* ssid     = "Grendene.Coletores";
const char* password = "ISO8804650216900479";

/*const char* ssid     = "Caetano";
const char* password = "992920940";*/
/*const char* ssid     = "Elisabeth_NossaNet";
const char* password = "34sup2bc9";*/

const int csPin = 18;          // LoRa radio chip select
const int resetPin = 14;       // LoRa radio reset

String outgoing;              // outgoing message

#define LED    LED_BUILTIN
#define SW     23

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0x05;     // address of this device

int timeZone = -3;
int indexHumidade =  1;
int lastIndexHumidade =  1;

String Gsender   = "00";
String Gincoming = "00";

long lastSendTimeOLED   = millis();
long lastSendTimeHQ     = millis();
long lastSendTimeHQ2    = millis();
long lastSendTimeHQ3    = millis();
long lastSendTimeJson   = millis();
long lastSendTimeBomba[6] = {millis(),millis(),millis(),millis(),millis(),millis()};

String stringComunicacao = "";
String stringComunicacao2 = "";

struct Date{
    int dayOfWeek;
    int day;
    int month;
    int year;
    int hours;
    int minutes;
};

//Socket UDP que a lib utiliza para recuperar dados sobre o horário
WiFiUDP udp;

//Objeto responsável por recuperar dados sobre horário
NTPClient ntpClient(
    udp,                    //socket udp
    "10.2.0.1",/*"2.br.pool.ntp.org",*/  //URL do server NTP
    timeZone*3600,          //Deslocamento do horário em relacão ao GMT 0
    60000);                 //Intervalo entre verificações online

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

int indice = 1;

String duracao = "m11111";
String hora[10] = {"maste","00:00","00:00","00:00","00:00","00:00"};
String s[10] = {"masterm","0000000","0000000","0000000","0000000","0000000"};
String umidade[10] = {"m","0","0","0","0","0"};
String bomba = "m00000";

String JSONtxt;
String jsonAddrArmaz;

void handleRoot(){
  server.send(200,"text/html", webpageCont);
}

//evento de processo de função: novos dados recebidos do cliente

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength){
  String payloadString = (const char *)payload;
 
  if(type == WStype_TEXT){
    
    byte separator=payloadString.indexOf('=');
    String var = payloadString.substring(0,separator);
    String val = payloadString.substring(separator+1);

    if(var == "DURACAO1"){
      duracao[1] = val[0];
      jsonAddrArmaz[50] = duracao[1];
    }
    if(var == "HORA1"){
      hora[1] = val;
      for (int i=0; i < hora[1].length(); i++){
        jsonAddrArmaz[71+i] = hora[1][i];
      }
    }
    if(var == "S1_0"){
      s[1] = val;
      for (int i=0; i < s[1].length(); i++){
        jsonAddrArmaz[93+i] = s[1][i];
      }
    }
       
    if(var == "DURACAO2"){
      duracao[2] = val[0];
      jsonAddrArmaz[158] = duracao[2];
    }
    if(var == "HORA2"){
      hora[2] = val;
      for (int i=0; i < hora[2].length(); i++){
        jsonAddrArmaz[179+i] = hora[2][i];
      }
    }
    if(var == "S2_0"){
      s[2] = val;
      for (int i=0; i < s[2].length(); i++){
        jsonAddrArmaz[201+i] = s[2][i];
      }
    }

    if(var == "DURACAO3"){
      duracao[3] = val[0];
      jsonAddrArmaz[266] = duracao[3];
    }
    if(var == "HORA3"){
      hora[3] = val;
      for (int i=0; i < hora[3].length(); i++){
        jsonAddrArmaz[287+i] = hora[3][i];
      }
    }
    if(var == "S3_0"){
      s[3] = val;
      for (int i=0; i < s[3].length(); i++){
        jsonAddrArmaz[309+i] = s[3][i];
      }
    }
    
    if(var == "DURACAO4"){
      duracao[4] = val[0];
      jsonAddrArmaz[374] = duracao[4];
    }
    if(var == "HORA4"){
      hora[4] = val;
      for (int i=0; i < hora[4].length(); i++){
        jsonAddrArmaz[395+i] = hora[4][i];
      }
    }
    if(var == "S4_0"){
      s[4] = val;
      for (int i=0; i < s[4].length(); i++){
        jsonAddrArmaz[417+i] = s[4][i];
      }
    }
    
    if(var == "DURACAO5"){
      duracao[5] = val[0];
      jsonAddrArmaz[482] = duracao[5];
    }
    if(var == "HORA5"){
      hora[5] = val;
      for (int i=0; i < hora[5].length(); i++){
        jsonAddrArmaz[503+i] = hora[5][i];
      }
    }
    if(var == "S5_0"){
      s[5] = val;
      for (int i=0; i < s[5].length(); i++){
        jsonAddrArmaz[525+i] = s[5][i];
      }
    }

    Serial.print(var);
    Serial.print(" --> ");
    Serial.println(val);
    writeFile(jsonAddrArmaz,"/addr.json",false);
    
  }
}


void setupNTP(){
    
    ntpClient.begin(); //Inicializa o client NTP
    
    Serial.println("FAZENDO UPDATE DO HORAsRIO"); //Espera pelo primeiro update online
    
    while(!ntpClient.update()){
        Serial.print(",");
        display.drawString(100,0, "NTP");
        display.display();
        ntpClient.forceUpdate();delay(500);
    }

    Serial.println();
    Serial.println("PRIMEIRO UPDATE DO HORAsRIO REALIZADO");
}

void wifiConnectionTask(void* param){
    while(true){
        if(WiFi.status() != WL_CONNECTED){
            connectWiFi();
        }
        vTaskDelay(100);
    }
}

void connectWiFi(){
  
    Serial.println("Conetando");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password); //Troque pelo nome e senha da sua rede WiFi
    
    while(WiFi.status() != WL_CONNECTED){ //Espera enquanto não estiver conectado
        Serial.print(".");
        display.drawString(60,15, "Wifi");
        display.display();
        delay(500);
    }

    Serial.println();
    Serial.print("IP ");
    Serial.println(WiFi.localIP().toString());
}

bool writeFile(String values, String pathFile, bool appending) {

  char *mode = "w";  //aberto para escrita (cria arquivo se não existir). Exclui o conteúdo e substitui o arquivo.
  if (appending) mode = "a";  //aberto para anexação (cria o arquivo se não existir)
  //Serial.println("- Writing file: " + pathFile);
  //Serial.println("- Values: " + values);
  SPIFFS.begin(true);
  File wFile = SPIFFS.open(pathFile, mode);
  if (!wFile) {
    Serial.println("- Falha ao escrever na pasta.");
    return false;
  } else {
    wFile.println(values);
    Serial.println("- Gravado!");
  }
  wFile.close();
  return true;
}


String readFile(String pathFile) {
  Serial.println("- Lendo: " + pathFile);
  SPIFFS.begin(true);
  File rFile = SPIFFS.open(pathFile, "r");
  String values;
  if (!rFile) {
    Serial.println("- Failed to open file.");
  } else {
    while (rFile.available()) {
      values += rFile.readString();
    }
    //Serial.println("- File values: " + values);
  }
  rFile.close();
  jsonAddrArmaz = values;
  return values;
}


void setup(){

  display.init();
  display.setFont(ArialMT_Plain_10); //10,16,24
  display.flipScreenVertically();

  display.drawString(0, 0, "IRRIGAÇÃO 4.0");
  display.display();
  delay(10);
 
  Serial.begin(9600);
  while (!Serial);
  pinMode(LED, OUTPUT);
  pinMode(A0, INPUT);

  LoRa.setPins(csPin, resetPin, LORA_DEFAULT_DIO0_PIN);// set CS, reset, IRQ 
  
  if(!LoRa.begin(915E6))while(true);
 
  Serial.println("LORA INICIADO");
  
  connectWiFi();
  setupNTP();
 
  server.on("/", handleRoot);
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  xTaskCreatePinnedToCore(
        wifiConnectionTask,     //Função que será executada
        "wifiConnectionTask",   //Nome da tarefa
        10000,                  //Tamanho da memória disponível (em WORDs)
        NULL,                   //Não vamos passar nenhum parametro
        NULL,                   //prioridade
        NULL,                   //Não precisamos de referência para a tarefa
        0);

  readFile("/addr.json");
  
  /*int i = 0;
  while(i < 2500){
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(jsonAddrArmaz[i]);
    Serial.println("*********");
    i++;
  }*/

  
  int dur = 50, hor = 71, sem = 93;
  for (int indice = 1; indice <= 5; indice++){
    duracao[indice] = jsonAddrArmaz[dur];
    hora[indice] = jsonAddrArmaz.substring(hor,hor+5);
    s[indice] = jsonAddrArmaz.substring(sem,sem+7);
    dur += 108;
    hor += 108;
    sem += 108;
  }

}

void escreveEJsonPUT(){
  JSONtxt = "{\"I\":\""+String(indice)+"\",";
  for (int ind = 1; ind <= 5; ind++){
    if(indice == ind)montaUmJsonIndex(duracao[ind], hora[ind], s[ind], umidade[ind], bomba[ind]);
  }
  if(indice > 5) indice = 1;
    
  Serial.println(JSONtxt);
  webSocket.broadcastTXT(JSONtxt);
}


void montaUmJsonIndex (char duracao, String horas, String s, String umidade, char bomba){
    JSONtxt += "\"D\":\""+String(duracao)+"\",";
    JSONtxt += "\"H\":\""+horas+"\",";
    JSONtxt += "\"S\":\""+s+"\",";
    JSONtxt += "\"U\":\""+umidade+"\",";
    JSONtxt += "\"B\":\""+String(bomba)+"\"}";
    indice++;
}


void loop() {

  Date date = getDate();
  webSocket.loop(); server.handleClient();

  if(lastSendTimeBomba[0] + 1000 < millis()){
    sendMessage("1RELE" + String(bomba[1]),0xe7);
    sendMessage("1RELE" + String(bomba[2]),0xe8);
    sendMessage("1RELE" + String(bomba[3]),0xe9);
    sendMessage("1RELE" + String(bomba[4]),0xea);
    sendMessage("1RELE" + String(bomba[5]),0xeb);
    lastSendTimeBomba[0] = millis();
  }

    String horas = String(date.hours);
    String minuto = String(date.minutes);
    if(date.hours < 10)horas = "0" + horas;
    if(date.minutes < 10)minuto = "0" + minuto;


    for (int indice = 1; indice <= 5; indice++){
      if((s[indice][date.dayOfWeek] == '1')&&(hora[indice] == horas + ":" + minuto)){
        bomba[indice] = '1';
        lastSendTimeBomba[indice] = millis(); 
      }
      else if((millis() > ((duracao[indice] - '0') * 300000) + lastSendTimeBomba[indice])&&(bomba[indice] == '1')){
        bomba[indice] = '0';
      }
    }
    
    if(lastSendTimeHQ + 60000 < millis()){
      indexHumidade = 1;
      lastSendTimeHQ = millis();
    }

    if(lastSendTimeHQ2 + 10000 < millis()){
      if(lastIndexHumidade != indexHumidade){
        lastIndexHumidade = indexHumidade;
      }else{
        indexHumidade++;
      }
      lastSendTimeHQ2 = millis();
    }

if(lastSendTimeHQ3 + 5000 < millis()){
    if(indexHumidade == 1)sendMessage("HQ",0xe7);
    else if(indexHumidade == 2)sendMessage("HQ",0xe8);
    else if(indexHumidade == 3)sendMessage("HQ",0xe9);
    else if(indexHumidade == 4)sendMessage("HQ",0xea);
    else if(indexHumidade == 5)sendMessage("HQ",0xeb);
    
    lastSendTimeHQ3 = millis();
}
  
if(lastSendTimeJson + 500 < millis()){
    escreveEJsonPUT();
    lastSendTimeJson = millis();
}
  
  onReceive(LoRa.parsePacket());

  if(lastSendTimeOLED + 500 < millis()){
    display.drawString(0, 0, "IRRIGAÇÃO 4.0");
    display.drawString(0,15, "LoRa OK");
    display.drawString(100,0, horas + ":" + minuto);
    display.drawString(60,15, WiFi.localIP().toString());
    display.drawString(0,30, stringComunicacao);
    display.drawString(0,45, stringComunicacao2);
    display.display();
    display.clear();
    lastSendTimeOLED = millis();
  }

}




Date getDate(){
    char* strDate = (char*)ntpClient.getFormattedDate().c_str(); //Recupera os dados de data e horário usando o client NTP
    Date date; //Passa os dados da string para a struct
    sscanf(strDate, "%d-%d-%dT%d:%d", 
                    &date.year, 
                    &date.month, 
                    &date.day, 
                    &date.hours, 
                    &date.minutes);
   
    date.dayOfWeek = ntpClient.getDay(); //Dia da semana de 0 a 6, sendo 0 o domingo
    return date;
}

void sendMessage(String outgoing,byte destination) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
  
  Serial.println("ENVIADO " + String(outgoing) + " PARA " + String(destination));

  stringComunicacao = "ENVIADO " + String(outgoing);
  stringComunicacao2 = "PARA " + String(destination);
}

void onReceive(int packetSize) {

  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length
 
  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
 
  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("Tamanho de mensagem não correspondente");
    return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  /*Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));*/
  Serial.println("Message: " + incoming);
 /* Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));*/
  Serial.println();

   if((String(sender, HEX) == "e7") && (String(incoming[0]) == "H")){
    umidade[1] = incoming;
   }
   if((String(sender, HEX) == "e8") && (String(incoming[0]) == "H")){
    umidade[2] = incoming;
   }
   if((String(sender, HEX) == "e9") && (String(incoming[0]) == "H")){
    umidade[3] = incoming;
   }
   if((String(sender, HEX) == "ea") && (String(incoming[0]) == "H")){
    umidade[4] = incoming;
   }
   if((String(sender, HEX) == "eb") && (String(incoming[0]) == "H")){
    umidade[5] = incoming;
   }

  Gsender = String(sender);
  Gincoming = String(incoming);
  
  stringComunicacao = "SLAVE " +Gsender + ": " + Gincoming;
  stringComunicacao2 = "RESPONDEU";
    
}

