//////MASTER

#include <LoRa.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <Wire.h>  
#include "SSD1306.h"
#include "webpage.h"

SSD1306 display(0x3c, 4, 15, 16); //Cria e ajusta o Objeto display

const char* ssid     = "Grendene.Coletores";
const char* password = "ISO8804650216900479";

const int csPin = 18;          // LoRa radio chip select
const int resetPin = 14;       // LoRa radio reset

String outgoing;              // outgoing message


#define LED LED_BUILTIN
#define SW     23


byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0x05;     // address of this device

int timeZone = -3;

long lastSendTimeHQ1    = millis();
long lastSendTimeHQ2    = millis();
long lastSendTimeHQ3    = millis();
long lastSendTimeHQ4    = millis();
long lastSendTimeHQ5    = millis();
long lastSendTimeBomba1 = millis();
long lastSendTimeBomba2 = millis();
long lastSendTimeBomba3 = millis();
long lastSendTimeBomba4 = millis();
long lastSendTimeBomba5 = millis();


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
    "10.2.0.1",             //URL do servwer NTP
    timeZone*3600,          //Deslocamento do horário em relacão ao GMT 0
    60000);                 //Intervalo entre verificações online


WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

int indice = 1;

char duracao1 = '1';
String hora1 = "00:00";
String s1_0 = "0000000";
String umidade1;
String bomba1 = "0";

char duracao2 = '1';
String hora2 = "00:00";
String s2_0 = "0000000";
String umidade2;
String bomba2 = "0";

char duracao3 = '1';
String hora3 = "00:00";
String s3_0 = "0000000";
String umidade3;
String bomba3 = "0";

char duracao4 = '1';
String hora4 = "00:00";
String s4_0 = "0000000";
String umidade4;
String bomba4 = "0";

char duracao5 = '1';
String hora5 = "00:00";
String s5_0 = "0000000";
String umidade5;
String bomba5 = "0";

String JSONtxt;

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

    if(var == "DURACAO1")duracao1 = val[0];
    if(var == "HORA1")hora1 = val;
    if(var == "S1_0")s1_0 = val;
    if(var == "BOMBA1")bomba1 = val;
    
    if(var == "DURACAO2")duracao2 = val[0];
    if(var == "HORA2")hora2 = val;
    if(var == "S2_0")s2_0 = val;

    if(var == "DURACAO3")duracao3 = val[0];
    if(var == "HORA3")hora3 = val;
    if(var == "S3_0")s3_0 = val;
    
    if(var == "DURACAO4")duracao4 = val[0];
    if(var == "HORA4")hora4 = val;
    if(var == "S4_0")s4_0 = val;
    
    if(var == "DURACAO5")duracao5 = val[0];
    if(var == "HORA5")hora5 = val;
    if(var == "S5_0")s5_0 = val;

  }
}


void setupNTP(){
    
    ntpClient.begin(); //Inicializa o client NTP
    
    Serial.println("FAZENDO UPDATE DO HORARIO"); //Espera pelo primeiro update online
    
    while(!ntpClient.update()){
        Serial.print(".");
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
        Serial.print("."); delay(500);
    }

    Serial.println();
    Serial.print("IP ");
    Serial.println(WiFi.localIP().toString());
}


void setup(){
 
  Serial.begin(9600);
  while (!Serial);
  pinMode(LED, OUTPUT);
  pinMode(A0, INPUT);

  LoRa.setPins(csPin, resetPin, LORA_DEFAULT_DIO0_PIN);// set CS, reset, IRQ 
  
  display.init();
  display.setFont(ArialMT_Plain_10); //10,16,24
  display.flipScreenVertically(); 


  
  if (!LoRa.begin(915E6)) {             // initialize ratio at 915 MHz
    Serial.println("INICIALIZAÇÃO LORA NÃO FOI ESTABELECIDA");
    while (true);                       // if failed, do nothing
  }
 
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


void loop() {

  Date date = getDate();
  webSocket.loop(); server.handleClient();

  Serial.printf("%d\n",date.dayOfWeek);
  Serial.printf("%d/%d\n",date.day, date.month);
  Serial.printf("%d:%d\n",date.hours, date.minutes);
 
  static unsigned long l = 0;
  unsigned long t = millis();

  String hora = String(date.hours);
  if(date.hours < 10){
    hora = "0" + hora;
  }

  String minuto = String(date.minutes);
  if(date.minutes < 10){
    minuto = "0" + minuto;
  }

    if((s1_0[date.dayOfWeek] == '1')&&(hora1 == hora + ":" + minuto)){
      bomba1 = "1";
      sendMessage("1RELE1",0xe7);
      lastSendTimeBomba1 = millis(); 
    }
    else if((millis()  > ((duracao1 - '0') * 300000) + lastSendTimeBomba1)&&(bomba1 == "1")) {
        bomba1 = "0";
        sendMessage("1RELE0",0xe7);
    }

    if((s2_0[date.dayOfWeek] == '1')&&(hora2 == hora + ":" + minuto)){
      bomba2 = "1";
      sendMessage("2RELE1",0xe6);
      lastSendTimeBomba2 = millis(); 
    }
    else if((millis() > ((duracao2 - '0') * 300000) + lastSendTimeBomba2)&&(bomba2 == "1")) {
      bomba2 = "0";
      sendMessage("2RELE0",0xe6);
    }
    
    if((s3_0[date.dayOfWeek] == '1')&&(hora3 == hora + ":" + minuto)){
      bomba3 = "1"; 
      lastSendTimeBomba3 = millis(); 
    }
    else if((millis() > ((duracao3 - '0') * 300000) + lastSendTimeBomba3)&&(bomba3 == "1")){
      bomba3 = "0";
    }
    
    if((s4_0[date.dayOfWeek] == '1')&&(hora4 == hora + ":" + minuto)){
      bomba4 = "1"; 
      lastSendTimeBomba4 = millis(); 
    }
    else if((millis() > ((duracao4 - '0') * 300000) + lastSendTimeBomba4)&&(bomba4 == "1")){
      bomba4 = "0";
    }
    
    if((s5_0[date.dayOfWeek] == '1')&&(hora5 ==  hora + ":" + minuto)){
      bomba5 = "1"; 
      lastSendTimeBomba5 = millis(); 
    }
    else if((millis() > ((duracao5 - '0') * 300000) + lastSendTimeBomba5)&&(bomba5 == "1")){
      bomba5 = "0";
    }

    if(millis() - lastSendTimeHQ1 > 10000) {
      sendMessage("HQ",0xe7);
      lastSendTimeHQ1 = millis();
    }
    
 
  if((t-l) > 1000){
   
    /*umidade1 = String(analogRead(A0));
    umidade2 = String(analogRead(A0));
    umidade3 = String(analogRead(A0));
    umidade4 = String(analogRead(A0));
    umidade5 = String(analogRead(A0));*/

    /*if(String(date.dayOfWeek) == s1_0[date.dayOfWeek]){
      printf("brasil");
    }*/
   

    JSONtxt = "{\"INDICE\":\""+String(indice)+"\",";
    if(indice == 1){
      JSONtxt += "\"DURACAO1\":\""+String(duracao1)+"\",";
      JSONtxt += "\"HORA1\":\""+hora1+"\",";
      JSONtxt += "\"S1_0\":\""+s1_0+"\",";
      JSONtxt += "\"UMIDADE1\":\""+umidade1+"\",";
      JSONtxt += "\"BOMBA1\":\""+bomba1+"\"}";
      indice = 2;
    }

    else if(indice == 2){
      JSONtxt += "\"DURACAO2\":\""+String(duracao2)+"\",";
      JSONtxt += "\"HORA2\":\""+hora2+"\",";
      JSONtxt += "\"S2_0\":\""+s2_0+"\",";
      JSONtxt += "\"UMIDADE2\":\""+umidade2+"\",";
      JSONtxt += "\"BOMBA2\":\""+bomba2+"\"}";
      indice = 3;
    }

    else if(indice == 3){
      JSONtxt += "\"DURACAO3\":\""+String(duracao3)+"\",";
      JSONtxt += "\"HORA3\":\""+hora3+"\",";
      JSONtxt += "\"S3_0\":\""+s3_0+"\",";
      JSONtxt += "\"UMIDADE3\":\""+umidade3+"\",";
      JSONtxt += "\"BOMBA3\":\""+bomba3+"\"}";
      indice = 4;
    }
    
    else if(indice == 4){
      JSONtxt += "\"DURACAO4\":\""+String(duracao4)+"\",";
      JSONtxt += "\"HORA4\":\""+hora4+"\",";
      JSONtxt += "\"S4_0\":\""+s4_0+"\",";
      JSONtxt += "\"UMIDADE4\":\""+umidade4+"\",";
      JSONtxt += "\"BOMBA4\":\""+bomba4+"\"}";
      indice = 5;
    }
    
    else if(indice == 5){
      JSONtxt += "\"DURACAO5\":\""+String(duracao5)+"\",";
      JSONtxt += "\"HORA5\":\""+hora5+"\",";
      JSONtxt += "\"S5_0\":\""+s5_0+"\",";
      JSONtxt += "\"UMIDADE5\":\""+umidade5+"\",";
      JSONtxt += "\"BOMBA5\":\""+bomba5+"\"}";
      indice = 1;
    }
    
    Serial.println(JSONtxt);
    webSocket.broadcastTXT(JSONtxt);
   
  }
  
  onReceive(LoRa.parsePacket());

  display.drawString(0, 0, "IRRIGAÇÃO 4.0");
  display.drawString(0,15, "LoRa OK");
  display.drawString(100,0, hora + ":" + minuto);
  display.drawString(60,15, WiFi.localIP().toString());
  display.display();
  delay(100);
  display.clear();
  delay(100);
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

  if(String(sender, HEX) == "1"){
    Serial.println(incoming);
  }

  
 
  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }
 
  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("This message is not for me.");
    return;                             // skip rest of function
  }
 
  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
}
