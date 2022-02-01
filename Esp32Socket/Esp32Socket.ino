//////MASTER
#include <LoRa.h>
#include <WiFi.h>
#include <WebServer.h>
#include <NTPClient.h>
#include <SPI.h>
#include <Wire.h>  
#include "SSD1306.h"
#include "webpage.h"
#include <WebSocketsServer.h>
#include <WiFiUdp.h>
#include <FS.h>
#include <SPIFFS.h> 


SSD1306 display(0x3c, 4, 15, 0); //Cria e ajusta o Objeto display

/*const char* ssid     = "Grendene.Coletores";
const char* password = "ISO8804650216900479";*/

const char* ssid     = "Caetano";
const char* password = "992920940";

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
long lastSendTimeJson   = millis();
long lastSendTimeHQ3    = millis();
long lastSendTimeBomba  = millis();
long lastSendTimeBomba1 = millis();
long lastSendTimeBomba2 = millis();
long lastSendTimeBomba3 = millis();
long lastSendTimeBomba4 = millis();
long lastSendTimeBomba5 = millis();

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
    /*"10.2.0.1",*/"2.br.pool.ntp.org",  //URL do server NTP
    timeZone*3600,          //Deslocamento do horário em relacão ao GMT 0
    60000);                 //Intervalo entre verificações online


WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

int indice = 1;

char duracao1 = '1';
String hora1 = "00:00";
String s1 = "0000000";
String umidade1 = "0";
char bomba1 = '0'; 

char duracao2 = '1';
String hora2 = "00:00";
String s2 = "0000000";
String umidade2 = "0";
char bomba2 = '0';

char duracao3 = '1';
String hora3 = "00:00";
String s3 = "0000000";
String umidade3 = "0";
char bomba3 = '0';

char duracao4 = '1';
String hora4 = "00:00";
String s4 = "0000000";
String umidade4 = "0";
char bomba4 = '0';

char duracao5 = '1';
String hora5 = "00:00";
String s5 = "0000000";
String umidade5 = "0";
char bomba5 = '0';

String JSONtxt;

void handleRoot(){
  server.send(200,"text/html", webpageCont);
}

String readFile(String pathFile) {
  Serial.println("- Reading file: " + pathFile);
  SPIFFS.begin(true);
  File rFile = SPIFFS.open(pathFile, "r");
  String values;
  if (!rFile) {
    Serial.println("- Failed to open file.");
  } else {
    while (rFile.available()) {
      values += rFile.readString();
    }
    Serial.println("- File values: " + values);
  }
  rFile.close();
  return values;
}

//evento de processo de função: novos dados recebidos do cliente

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength){
  String payloadString = (const char *)payload;

  readFile("/addr.json");
  
  if(type == WStype_TEXT){
    
    byte separator = payloadString.indexOf('=');
    String var = payloadString.substring(0,separator);
    String val = payloadString.substring(separator+1);

    if(var == "DURACAO1")duracao1 = val[0];
    if(var == "HORA1")hora1 = val;
    if(var == "S1_0")s1 = val;
       
    if(var == "DURACAO2")duracao2 = val[0];
    if(var == "HORA2")hora2 = val;
    if(var == "S2_0")s2 = val;

    if(var == "DURACAO3")duracao3 = val[0];
    if(var == "HORA3")hora3 = val;
    if(var == "S3_0")s3 = val;
    
    if(var == "DURACAO4")duracao4 = val[0];
    if(var == "HORA4")hora4 = val;
    if(var == "S4_0")s4 = val;
    
    if(var == "DURACAO5")duracao5 = val[0];
    if(var == "HORA5")hora5 = val;
    if(var == "S5_0")s5 = val;
    
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
    Serial.println("PRIMEIRO UPDATE DO HORARIO REALIZADO");
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

}

void escreveEJsonPUT(){
  JSONtxt = "{\"I\":\""+String(indice)+"\",";
       if(indice == 1)montaUmJsonIndex(duracao1, hora1, s1, umidade1, bomba1);
  else if(indice == 2)montaUmJsonIndex(duracao2, hora2, s2, umidade2, bomba2);
  else if(indice == 3)montaUmJsonIndex(duracao3, hora3, s3, umidade3, bomba3);
  else if(indice == 4)montaUmJsonIndex(duracao4, hora4, s4, umidade4, bomba4);
  else if(indice == 5)montaUmJsonIndex(duracao5, hora5, s5, umidade5, bomba5);
  else indice = 1;
    
  ///--Serial.println(JSONtxt);
  webSocket.broadcastTXT(JSONtxt);
}

void estadoBomba(Date date, String hora, String minuto){
  
    if((s1[date.dayOfWeek] == '1')&&(hora1 == hora + ":" + minuto)){
      bomba1 = '1';
      lastSendTimeBomba1 = millis(); 
    }
    else if((millis() > ((duracao1 - '0') * 300000) + lastSendTimeBomba1)&&(bomba1 == '1')){
      bomba1 = '0';
    }

    if((s2[date.dayOfWeek] == '1')&&(hora2 == hora + ":" + minuto)){
      bomba2 = '1';
      lastSendTimeBomba2 = millis(); 
    }
    else if((millis() > ((duracao2 - '0') * 300000) + lastSendTimeBomba2)&&(bomba2 == '1')){
      bomba2 = '0';
    }
    
    if((s3[date.dayOfWeek] == '1')&&(hora3 == hora + ":" + minuto)){
      bomba3 = '1'; 
      lastSendTimeBomba3 = millis(); 
    }
    else if((millis() > ((duracao3 - '0') * 300000) + lastSendTimeBomba3)&&(bomba3 == '1')){
      bomba3 = '0';
    }
    
    if((s4[date.dayOfWeek] == '1')&&(hora4 == hora + ":" + minuto)){
      bomba4 = '1'; 
      lastSendTimeBomba4 = millis(); 
    }
    else if((millis() > ((duracao4 - '0') * 300000) + lastSendTimeBomba4)&&(bomba4 == '1')){
      bomba4 = '0';
    }
    
    if((s5[date.dayOfWeek] == '1')&&(hora5 ==  hora + ":" + minuto)){
      bomba5 = '1'; 
      lastSendTimeBomba5 = millis(); 
    }
    else if((millis() > ((duracao5 - '0') * 300000) + lastSendTimeBomba5)&&(bomba5 == '1')){
      bomba5 = '0';
    }

}   


void montaUmJsonIndex (char duracao, String hora, String s, String umidade, char bomba){
    JSONtxt += "\"D\":\""+String(duracao)+"\",";
    JSONtxt += "\"H\":\""+hora+"\",";
    JSONtxt += "\"S\":\""+s+"\",";
    JSONtxt += "\"U\":\""+umidade+"\",";
    JSONtxt += "\"B\":\""+String(bomba)+"\"}";
    indice++;
}


void loop() {

  Date date = getDate();
  webSocket.loop(); server.handleClient();

  if(lastSendTimeBomba + 1000 < millis()){
    sendMessage("1RELE" + String(bomba1),0xe7);
    sendMessage("1RELE" + String(bomba2),0xe8);
    sendMessage("1RELE" + String(bomba3),0xe9);
    sendMessage("1RELE" + String(bomba4),0xea);
    sendMessage("1RELE" + String(bomba5),0xeb);
    lastSendTimeBomba = millis();
  }

    String hora = String(date.hours);
    String minuto = String(date.minutes);
    if(date.hours < 10)hora = "0" + hora;
    if(date.minutes < 10)minuto = "0" + minuto;
    
    estadoBomba(date,hora,minuto);

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
    display.drawString(100,0, hora + ":" + minuto);
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
  
  ///--Serial.println("ENVIADO " + String(outgoing) + " PARA " + String(destination));

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
    umidade1 = incoming;
   }
   if((String(sender, HEX) == "e8") && (String(incoming[0]) == "H")){
    umidade2 = incoming;
   }
   if((String(sender, HEX) == "e9") && (String(incoming[0]) == "H")){
    umidade3 = incoming;
   }
   if((String(sender, HEX) == "ea") && (String(incoming[0]) == "H")){
    umidade4 = incoming;
   }
   if((String(sender, HEX) == "eb") && (String(incoming[0]) == "H")){
    umidade5 = incoming;
   }

  Gsender = String(sender);
  Gincoming = String(incoming);
  
  stringComunicacao = "SLAVE " +Gsender + ": " + Gincoming;
  stringComunicacao2 = "RESPONDEU";
    
}
