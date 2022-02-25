//////MASTER
#include <LoRa.h>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <Wire.h>  
#include <FS.h>
#include <SPIFFS.h> 
#include "SSD1306.h"
#include "webpage.h"

/*const char* ssid     = "Grendene.Coletores";
const char* password = "ISO8804650216900479";*/

/*const char* ssid     = "Caetano";
const char* password = "992920940";*/

const char* ssid     = "Elisabeth_NossaNet";
const char* password = "34sup2bc9";

const byte csPin = 18;          // LoRa radio chip select
const byte resetPin = 14;       // LoRa radio reset

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0x00;     // address of this device

int timeZone = -3;
byte indexHumidade =  1;

long millisAtualizacaoDisplay = millis();
long tempoEmCadaSlave         = millis();
long intervaloEntreMensagens  = millis();
long tempoDeReenvioJson       = millis();
long lastSendTimeBomba[6]     ={millis(),millis(),millis(),millis(),millis(),millis()};

SSD1306 display(0x3c, 4, 15, 0); //Cria e ajusta o Objeto display

String stringComunicacao = "";
String stringComunicacao2 = "";

StaticJsonDocument<2560> jsonDoc;

struct Date{int dayOfWeek; int day; int month; int year; int hours; int minutes;};

//Socket UDP que a lib utiliza para recuperar dados sobre o horário
WiFiUDP udp;

//Objeto responsável por recuperar dados sobre horário
NTPClient ntpClient(
    udp,                    //socket udp
    /*"10.2.0.1",*/"2.br.pool.ntp.org",  //URL do server NTP
    timeZone*3600,          //Deslocamento do horário em relacão ao GMT 0
    60000);                 //Intervalo entre verificações online

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

byte indice = 1;

String hora[10],s[10],umidade[10],bomba = "m00000";
int duracao[10];

String JSONtxt;
String jsonAddrArmaz;

char socketAberto = '0';

void handleRoot(){
  server.send(200,"text/html",webpageCont);/*+String(webpageCont2)*/
  Serial.println(""###############################################");
}

//evento de processo de função: novos dados recebidos do cliente
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength){
  String payloadString = (const char *)payload;
 
  if(type == WStype_TEXT){
    byte separator = payloadString.indexOf('=');
    String var = payloadString.substring(0,separator);
    String val = payloadString.substring(separator+1);
    
  for(byte endrc = 1; endrc <= 5; endrc++){
    if(var == "DURACAO" + String(endrc)){
      jsonDoc[endrc]["duracao"] = val;
    }
    if(var == "HORA" + String(endrc)){
      jsonDoc[endrc]["hora"] = val;
    }
    if(var == "S" + String(endrc)){
      jsonDoc[endrc]["s"] = val;
    }
  }
  //String gravaJson = "";
  //(gravaJson, jsonDoc);
  //writeFile(gravaJson,"/addr.json",false);
  }
}

void lerJsonIrrigacao(){
  for (int indice = 1; indice <= 5; indice++){
    duracao[indice] = jsonDoc[indice]["duracao"];
  }
}

void setupNTP(){
    
    ntpClient.begin(); //Inicializa o client NTP
    Serial.println("FAZENDO UPDATE DO HORARIO"); //Espera pelo primeiro update online
    
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
    
    Serial.print("IP ");
    Serial.println(WiFi.localIP().toString());
}

bool writeFile(String values, String pathFile, bool appending) {
  char *mode = "w";  //aberto para escrita (cria arquivo se não existir). Exclui o conteúdo e substitui o arquivo.
  if (appending) mode = "a";  //aberto para anexação (cria o arquivo se não existir)
  SPIFFS.begin(true);
  File wFile = SPIFFS.open(pathFile, mode);
  if (!wFile) {
    Serial.println("- Falha ao escrever na pasta.");
    return false;
  } else {
    wFile.println(values);
    //Serial.println(values);
    Serial.println("- Gravado!");
  }
  wFile.close();
  return true;
}


String readFile(String pathFile){
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
  }
  rFile.close();
  jsonAddrArmaz = values;
  return values;
}

void displayInit(){
  delay(10);
  display.init();
  display.setFont(ArialMT_Plain_10); //10,16,24
  display.flipScreenVertically();
  display.drawString(0, 0, "IRRIGAÇÃO 4.0");
  display.display();
}

void LoraBegin(){
  LoRa.setPins(csPin, resetPin, LORA_DEFAULT_DIO0_PIN);// set CS, reset, IRQ 
  if(!LoRa.begin(915E6))while(true);
  Serial.println("LORA INICIADO");
}

void webSocketInit(){
  server.on("/", handleRoot);
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  xTaskCreatePinnedToCore(wifiConnectionTask,"wifiConnectionTask",10000, NULL,NULL,NULL,0);
}

void escreveEJsonPUT(){
  JSONtxt = "{\"I\":\""+String(indice)+"\",";
  montaUmJsonIndex(jsonDoc[indice]["duracao"], jsonDoc[indice]["hora"], jsonDoc[indice]["s"], umidade[indice], bomba[indice]);
  if(indice > 5) indice = 1;
  Serial.println(JSONtxt);
  webSocket.broadcastTXT(JSONtxt);
} 

void montaUmJsonIndex(int duracao, String hora, String s, String umidade, char bomba){
    JSONtxt += "\"D\":\""+String(duracao)+"\",\"H\":\""+hora+"\",\"S\":\""+s+"\",\"U\":\""+umidade+"\",\"B\":\""+String(bomba)+"\"}";
    indice++;
}

void acionamentoBomba(){
    Date date = getDate();
    String horas = String(date.hours);
    String minuto = String(date.minutes);
    if(date.hours < 10)horas = "0" + horas;
    if(date.minutes < 10)minuto = "0" + minuto;
    
    for (int in = 1; in <= 5; in++){
      duracao[in] = jsonDoc[in]["duracao"];
      if((jsonDoc[in]["s"][date.dayOfWeek] == '1')&&(jsonDoc[in]["hora"] == horas + ":" + minuto)){
        bomba[in] = '1';
        lastSendTimeBomba[indice] = millis(); 
      }
      else if((millis() > ((duracao[in]) * 300000) + lastSendTimeBomba[indice])&&(bomba[in] == '1')){
        bomba[in] = '0';
      }
    }
    sendMessage("1RELE" + String(bomba[indice]),indice);
}

long callBack(void (*func)(), long variavel, int tempo){ 
  if(variavel + tempo < millis()){
    (*func)();
    variavel = millis();
  }
  return variavel;
} 

void WaitDogSlave(){
  indexHumidade++;
  if(indexHumidade>5)indexHumidade=1;
}

void escreveDisplay(){/*String horas, String minuto*/
    display.drawString(0, 0, "IRRIGAÇÃO 4.0");
    display.drawString(0,15, "LoRa OK");
    //display.drawString(100,0, horas + ":" + minuto);
    display.drawString(60,15, WiFi.localIP().toString());
    display.drawString(0,30, stringComunicacao);
    display.drawString(0,45, stringComunicacao2);
    display.display();
    display.clear();
}

Date getDate(){
    char* strDate = (char*)ntpClient.getFormattedDate().c_str(); //Recupera os dados de data e horário usando o client NTP
    Date date; //Passa os dados da string para a struct
    sscanf(strDate,"%d-%d-%dT%d:%d",&date.year,&date.month,&date.day,&date.hours,&date.minutes);
    date.dayOfWeek = ntpClient.getDay(); //Dia da semana de 0 a 6, sendo 0 o domingo
    return date;
}

void sendMessage(String outgoing,byte destination){
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
    return;                    
  }

  Serial.println("Recebido de: " + String(sender, HEX));
  Serial.println("Enviado para: " + String(recipient, HEX));
  /*Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));*/
  Serial.println("Messagem: " + incoming);
 /* Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));*/
  Serial.println();
  
  for (int ind = 1; ind <= 5; ind++){
   if((sender == ind) && (String(incoming[0]) == "H")){
     umidade[ind] = incoming;
   }
  }
  
  stringComunicacao = "SLAVE " + String(sender) + ": " + String(incoming);
  stringComunicacao2 = "RESPONDEU";
}

void setup(){
  Serial.begin(9600);
  
  displayInit();
  LoraBegin();
  connectWiFi();
  setupNTP();
  webSocketInit();

  String input = readFile("/addr.json");
  deserializeJson(jsonDoc, input);
  lerJsonIrrigacao();
}

void loop() {
  void (*_escreveEJsonPUT)()=&escreveEJsonPUT, (*_escreveDisplay)()=&escreveDisplay, (*_acionamentoBomba)()=&acionamentoBomba, (*_WaitDogSlave)()=&WaitDogSlave;    //, (*_sendMessage)("HQ",indexHumidade)=&sendMessage; //
  
  webSocket.loop(); server.handleClient();

  tempoDeReenvioJson = callBack(*_escreveEJsonPUT,tempoDeReenvioJson,512);
  millisAtualizacaoDisplay = callBack(*_escreveDisplay,millisAtualizacaoDisplay,755);///*horas, minuto*/
  lastSendTimeBomba[0] = callBack(*_acionamentoBomba,lastSendTimeBomba[0],3070);
  tempoEmCadaSlave = callBack(*_WaitDogSlave,tempoEmCadaSlave,10000);
  //intervaloEntreMensagens = callBack(*_sendMessage,intervaloEntreMensagens,5000);
  
  if(intervaloEntreMensagens + 5000 < millis()){
    sendMessage("HQ",indexHumidade);
    intervaloEntreMensagens = millis();
  }
  onReceive(LoRa.parsePacket());
}
