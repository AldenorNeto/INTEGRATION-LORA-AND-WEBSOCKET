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

String duracao1 = "0";
String hora1 = "00:00";
String s1_0, s1_1, s1_2, s1_3, s1_4, s1_5, s1_6;
String umidade1;
String bomba1;

String duracao2 = "0";
String hora2 = "00:00";
String s2_0, s2_1, s2_2, s2_3, s2_4, s2_5, s2_6;
String umidade2;
String bomba2;

String duracao3 = "0";
String hora3 = "00:00";
String s3_0, s3_1, s3_2, s3_3, s3_4, s3_5, s3_6;
String umidade3;
String bomba3;

String duracao4 = "0";
String hora4 = "00:00";
String s4_0, s4_1, s4_2, s4_3, s4_4, s4_5, s4_6;
String umidade4;
String bomba4;

String duracao5 = "0";
String hora5 = "00:00";
String s5_0, s5_1, s5_2, s5_3, s5_4, s5_5, s5_6;
String umidade5;
String bomba5;


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

    if(var == "DURACAO1"){
          duracao1 = val;
    }
    if(var == "HORA1"){
          hora1 = val;
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


    if(var == "DURACAO2"){
          duracao2 = val;
    }
    if(var == "HORA2"){
          hora2 = val;
    }
    
    if(var == "S2_0"){
          s2_0 = val;
    }
    if(var == "S2_1"){
          s2_1 = val;
    }
    if(var == "S2_2"){
          s2_2 = val;
    }
    if(var == "S2_3"){
          s2_3 = val;
    }
    if(var == "S2_4"){
          s2_4 = val;
    }
    if(var == "S2_5"){
          s2_5 = val;
    }
    if(var == "S2_6"){
          s2_6 = val;
    }


    if(var == "DURACAO3"){
          duracao3 = val;
    }
    if(var == "HORA3"){
          hora3 = val;
    }
    
    if(var == "S3_0"){
          s3_0 = val;
    }
    if(var == "S3_1"){
          s3_1 = val;
    }
    if(var == "S3_2"){
          s3_2 = val;
    }
    if(var == "S3_3"){
          s3_3 = val;
    }
    if(var == "S3_4"){
          s3_4 = val;
    }
    if(var == "S3_5"){
          s3_5 = val;
    }
    if(var == "S3_6"){
          s3_6 = val;
    }


    if(var == "DURACAO4"){
          duracao4 = val;
    }
    if(var == "HORA4"){
          hora4 = val;
    }
    
    if(var == "S4_0"){
          s4_0 = val;
    }
    if(var == "S4_1"){
          s4_1 = val;
    }
    if(var == "S4_2"){
          s4_2 = val;
    }
    if(var == "S4_3"){
          s4_3 = val;
    }
    if(var == "S4_4"){
          s4_4 = val;
    }
    if(var == "S4_5"){
          s4_5 = val;
    }
    if(var == "S4_6"){
          s4_6 = val;
    }
    

    if(var == "DURACAO5"){
          duracao5 = val;
    }
    if(var == "HORA5"){
          hora5 = val;
    }
    
    if(var == "S5_0"){
          s5_0 = val;
    }
    if(var == "S5_1"){
          s5_1 = val;
    }
    if(var == "S5_2"){
          s5_2 = val;
    }
    if(var == "S5_3"){
          s5_3 = val;
    }
    if(var == "S5_4"){
          s5_4 = val;
    }
    if(var == "S5_5"){
          s5_5 = val;
    }
    if(var == "S5_6"){
          s5_6 = val;
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
    
    umidade1 = String(analogRead(A0));
    umidade2 = String(analogRead(A0));
    umidade3 = String(analogRead(A0));
    umidade4 = String(analogRead(A0));
    umidade5 = String(analogRead(A0));

    JSONtxt  = "{\"DURACAO1\":\""+duracao1+"\",";
    JSONtxt += "\"HORA1\":\""+hora1+"\",";
    JSONtxt += "\"S1_0\":\""+s1_0+"\","+"\"S1_1\":\""+s1_1+"\","+"\"S1_2\":\""+s1_2+"\","+"\"S1_3\":\""+s1_3+"\","+"\"S1_4\":\""+s1_4+"\","+"\"S1_5\":\""+s1_5+"\","+"\"S1_6\":\""+s1_6+"\",";
    JSONtxt += "\"UMIDADE1\":\""+umidade1+"\",";
    JSONtxt += "\"BOMBA1\":\""+bomba1+"\"}";

    JSONtxt  = "{\"DURACAO2\":\""+duracao2+"\",";
    JSONtxt += "\"HORA2\":\""+hora2+"\",";
    JSONtxt += "\"S2_0\":\""+s2_0+"\","+"\"S2_1\":\""+s2_1+"\","+"\"S2_2\":\""+s2_2+"\","+"\"S2_3\":\""+s2_3+"\","+"\"S2_4\":\""+s2_4+"\","+"\"S2_5\":\""+s2_5+"\","+"\"S2_6\":\""+s2_6+"\",";
    JSONtxt += "\"UMIDADE2\":\""+umidade2+"\",";
    JSONtxt += "\"BOMBA2\":\""+bomba2+"\"}";

    JSONtxt  = "{\"DURACAO3\":\""+duracao3+"\",";
    JSONtxt += "\"HORA3\":\""+hora3+"\",";
    JSONtxt += "\"S3_0\":\""+s3_0+"\","+"\"S3_1\":\""+s3_1+"\","+"\"S3_2\":\""+s3_2+"\","+"\"S3_3\":\""+s3_3+"\","+"\"S3_4\":\""+s3_4+"\","+"\"S3_5\":\""+s3_5+"\","+"\"S3_6\":\""+s3_6+"\",";
    JSONtxt += "\"UMIDADE3\":\""+umidade3+"\",";
    JSONtxt += "\"BOMBA3\":\""+bomba3+"\"}";

    JSONtxt  = "{\"DURACAO4\":\""+duracao4+"\",";
    JSONtxt += "\"HORA4\":\""+hora4+"\",";
    JSONtxt += "\"S4_0\":\""+s4_0+"\","+"\"S4_1\":\""+s4_1+"\","+"\"S4_2\":\""+s4_2+"\","+"\"S4_3\":\""+s4_3+"\","+"\"S4_4\":\""+s4_4+"\","+"\"S4_5\":\""+s4_5+"\","+"\"S4_6\":\""+s4_6+"\",";
    JSONtxt += "\"UMIDADE4\":\""+umidade4+"\",";
    JSONtxt += "\"BOMBA4\":\""+bomba4+"\"}";
    
    JSONtxt  = "{\"DURACAO5\":\""+duracao5+"\",";
    JSONtxt += "\"HORA5\":\""+hora5+"\",";
    JSONtxt += "\"S5_0\":\""+s5_0+"\","+"\"S5_1\":\""+s5_1+"\","+"\"S5_2\":\""+s5_2+"\","+"\"S5_3\":\""+s5_3+"\","+"\"S5_4\":\""+s5_4+"\","+"\"S5_5\":\""+s5_5+"\","+"\"S5_6\":\""+s5_6+"\",";
    JSONtxt += "\"UMIDADE5\":\""+umidade5+"\",";
    JSONtxt += "\"BOMBA5\":\""+bomba5+"\"}";


    Serial.println(JSONtxt);
    webSocket.broadcastTXT(JSONtxt);
    
  }
}
