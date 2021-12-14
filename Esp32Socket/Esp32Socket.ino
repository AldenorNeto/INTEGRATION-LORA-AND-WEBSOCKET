#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

#define LED LED_BUILTIN
#define SW     23

const char* ssid     = "Grendene.Coletores";
const char* password = "ISO8804650216900479";

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

String LEDonoff;
boolean faustino=false;
String duracao;
String hora;
String s1_0, s1_1, s1_2, s1_3, s1_4, s1_5, s1_6;
String umidade;
String bomba;


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

    if(var == "DURACAO"){
          duracao = val;
    }
    if(var == "HORA"){
          hora = val;
    }
    
    if(var == "S1_0"){
          s1_0 = val;
    }
    if(var == "S1_1"){
          s1_1 = val;
    }
    if(var == "S1_2"){
          s1_2 = val;
    }
    if(var == "S1_3"){
          s1_3 = val;
    }
    if(var == "S1_4"){
          s1_4 = val;
    }
    if(var == "S1_5"){
          s1_5 = val;
    }
    if(var == "S1_6"){
          s1_6 = val;
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
    
    umidade = String(analogRead(A0));

    JSONtxt  = "{\"DURACAO\":\""+duracao+"\",";
    JSONtxt += "\"HORA\":\""+hora+"\",";
    JSONtxt += "\"S1_0\":\""+s1_0+"\","+"\"S1_1\":\""+s1_1+"\","+"\"S1_2\":\""+s1_2+"\","+"\"S1_3\":\""+s1_3+"\","+"\"S1_4\":\""+s1_4+"\","+"\"S1_5\":\""+s1_5+"\","+"\"S1_6\":\""+s1_6+"\",";
    JSONtxt += "\"UMIDADE\":\""+umidade+"\",";
    JSONtxt += "\"BOMBA\":\""+bomba+"\"}";

    Serial.println(JSONtxt);
    webSocket.broadcastTXT(JSONtxt);
    
  }
}
