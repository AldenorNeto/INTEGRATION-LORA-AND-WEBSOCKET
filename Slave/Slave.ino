//////SLAVE
#include <Wire.h> 
#include "SSD1306.h"
#include <SPI.h>
#include <LoRa.h>

#define RELE1 17
 
const int csPin = 18;          // LoRa radio chip select
const int resetPin = 14;       // LoRa radio reset
 
String outgoing;              // outgoing message
bool senderSlave = false;
 
byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xe7;     // address of this device
byte destination = 0x05;      // destination to send to

SSD1306 display(0x3c, 4, 15, 16); //Cria e ajusta o Objeto display


byte Gsender; 
String Gincoming = "";
int Grecipient = 0;
 
void setup() {
  
  Serial.begin(9600);                   // initialize serial
  while (!Serial);

  pinMode(RELE1, OUTPUT);
  pinMode(A0, INPUT);
 
  // override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, LORA_DEFAULT_DIO0_PIN);// set CS, reset, IRQ pin
 
  if(!LoRa.begin(915E6)){             // initialize ratio at 915 MHz
    Serial.println("INICIALIZAÇÃO LORA DO SLAVE NÃO FOI ESTABELECIDA");
    while (true);                       // if failed, do nothing
  }
 
  Serial.println("INICIANDO SLAVE LORA");
  digitalWrite(RELE1,1);

  display.init();
  display.setFont(ArialMT_Plain_10); //10,16,24
  display.flipScreenVertically(); 

}
 
void loop(){
  
  

 
  //analise um pacote e chama onReceive com o resultado:
  onReceive(LoRa.parsePacket());
 
  display.drawString(0, 0, "IRRIGAÇÃO 4.0");
  display.drawString(0,15, "ADDR: " + String(localAddress));
  display.drawString(60,15, "UMID: " + String((analogRead(A0) * 100)/4095) + "%");
  display.drawString(0, 30, "Send " + String(Gsender, HEX) + ":  " + Gincoming);
  if(Grecipient != localAddress){
    display.drawString(0, 45, "For " + String(Grecipient));
  }
  else{
    display.drawString(0, 45, "For Me");
    if(senderSlave){
      
      if(Gincoming == "HQ"){
        String message = String(analogRead(A0));
        sendMessage(message);
        Serial.println("Enviado: " + message);
        senderSlave = false; 
      }
    }
  }


  display.display();
  delay(100);
  display.clear();
  delay(100);

  if(Gincoming == "1RELE1"){
     digitalWrite(RELE1,0);
  }else if(Gincoming == "1RELE0"){
     digitalWrite(RELE1,1);
  }
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
 
void onReceive(int packetSize){

  if(packetSize == 0) return;          // if there's no packet, return
 
  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  String incoming = "";
 
  while(LoRa.available()){
    incoming += (char)LoRa.read();
  }
 
  if(incomingLength != incoming.length()){   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }
  
  Gsender = sender;
  Gincoming = incoming;
  Grecipient = recipient;
  
  // if the recipient isn't this device or broadcast,
  if(recipient != localAddress && recipient != 0xFF){
    Serial.print("MESSAGEM PARA O SLAVE ");
    Serial.println(recipient);
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


  

  
  senderSlave = true;
}
