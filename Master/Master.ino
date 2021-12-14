//////MASTER
#include <SPI.h>              // include libraries
#include <LoRa.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "webpage.h"

WebServer server(80);
const char* ssid     = "Caetano";
const char* password = "992920940";

const int csPin = 18;          // LoRa radio chip select
const int resetPin = 14;       // LoRa radio reset
 
String outgoing;              // outgoing message

bool led = false;
String potpot1 = "";
String potpot2 = "";
 
byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0x05;     // address of this device
byte destination = 0x01;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 2000;          // interval between sends


//---------------------------------------------------
void handleRoot(){
 server.send(200, "text/html", webpageCode);
}

//---------------------------------------
void handlePOT(){
 String POTval = (potpot1+"-"+potpot2);//analogRead(38));
 server.send(200, "text/plane", POTval);
}

//===================================================
 
void setup() {
  
  Serial.begin(9600);                   // initialize serial
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
  
  while (!Serial);
 
  // override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, LORA_DEFAULT_DIO0_PIN);// set CS, reset, IRQ pin
 
  if (!LoRa.begin(915E6)) {             // initialize ratio at 915 MHz
    Serial.println("INICIALIZAÇÃO LORA NÃO FOI ESTABELECIDA");
    while (true);                       // if failed, do nothing
  }
 
  Serial.println("LORA INICIADO");

  //-------------------------------------------------
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while(WiFi.waitForConnectResult() != WL_CONNECTED){
    delay(500); Serial.print(".");
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //-------------------------------------------------
  server.on("/", handleRoot);
  server.on("/readPOT", handlePOT);
  server.begin();
  Serial.println("SERVIDOR HTTP INCIADO");
  
}
 
void loop() {
  if (millis() - lastSendTime > interval) {
    String message = "HeLoRa World!";   // send a message
    sendMessage(message);
    Serial.println("Sending " + message);
    lastSendTime = millis();            // timestamp the message
    interval = random(5000) + 1000;    // 2-3 seconds
    if(led){
      led = false;
      destination = 0x02;
    }else{
      led=true;
      destination = 0x01;
    }
  }
  digitalWrite(LED_BUILTIN,led);

  server.handleClient(); delay(1);
 

  onReceive(LoRa.parsePacket());
}
 
void sendMessage(String outgoing) {
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
    potpot1 = incoming;
  }
  if(String(sender, HEX) == "2"){
    potpot2 = incoming;
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











/*


#include <iostream>
#include <cstring>
using namespace std;
void setup(){
  
Serial.begin(9600);
Serial.println();
    string s = "geeksforgeeks";

    int n = s.length();
 
    // declaring character array
    char char_array[n + 1];
 
    // copying the contents of the
    // string to char array
    strcpy(char_array, s.c_str());
 
    for (int i = 0; i < n; i++)
        Serial.println(char_array[i]);
}

void loop() {

}*/

 
