#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

#define LED LED_BUILTIN
#define SW     23

const char* ssid     = "Caetano";
const char* password = "992920940";

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

boolean LEDonoff=false;
boolean faustino=false;
String JSONtxt;

#include "webpage.h"

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
    
    if(var == "LEDonoff"){
      LEDonoff = false;
      if(val == "ON") LEDonoff = true;
    }
    if(var == "faustino"){
      faustino = false;
      if(val == "ON") faustino = true;
    }
  }
}

void setup(){
  
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(A0, INPUT);
  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print("."); delay(500);  
  }
  WiFi.mode(WIFI_STA);
  Serial.print(" Local IP: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot);
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  
  webSocket.loop(); server.handleClient();
  
  static unsigned long l = 0;
  unsigned long t = millis();
  
  if((t-l) > 1000){
    
    if(LEDonoff == false || faustino == false) digitalWrite(LED, LOW);
    else digitalWrite(LED, HIGH);
    String LEDstatus = "OFF";
    String oloko = "baixo";
    if(LEDonoff == true) LEDstatus = "ON";
    if(faustino == true) oloko = "ON";
    
    String TEMPvalString = String(analogRead(A0));

    JSONtxt  = "{\"TEMP\":\""+TEMPvalString+"\",";
    JSONtxt += "\"LEDonoff\":\""+LEDstatus+"\",";
    JSONtxt += "\"faustino\":\""+oloko+"\"}";

    Serial.println(JSONtxt);
    webSocket.broadcastTXT(JSONtxt);
    
  }
}
