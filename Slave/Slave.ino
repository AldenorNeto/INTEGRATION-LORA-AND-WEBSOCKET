//////SLAVE
#include <Wire.h> 
#include "SSD1306.h"
#include <SPI.h>
#include <LoRa.h>

#define RELE1    17
#define RELE2    23
#define divisor1 36
#define divisor2 37
#define sensor   38 

 
const int csPin = 18;          // LoRa radio chip select
const int resetPin = 14;       // LoRa radio reset

<<<<<<< HEAD
long lastSendTimeOLED = millis();
long intervaloSemLoRa = millis();
bool RedeON = 0;
=======
long lastSendTimeOLED   = millis();
>>>>>>> 108c3ec33b59e7d4a351f423cd137c2a34a45eb5
 
String outgoing;              // outgoing message
bool senderSlave = false;
 
<<<<<<< HEAD
byte msgCount = 0, localAddress = 1, Master = 250;      
=======
byte msgCount = 0;         // count of outgoing messages
byte localAddress = 1;     // address of this device
byte Master = 250;

byte sender; int recipient; String incoming;
>>>>>>> 108c3ec33b59e7d4a351f423cd137c2a34a45eb5

SSD1306 display(0x3c, 4, 15, 16); //Cria e ajusta o Objeto display
 
void setup() {
  
  Serial.begin(9600);
  while (!Serial);

  digitalWrite(RELE2,1);
  pinMode(0, INPUT);
  pinMode(RELE2, OUTPUT);

  pinMode(23, OUTPUT);
  pinMode(divisor1, INPUT);
  
  display.init();
  display.setFont(ArialMT_Plain_10); //10,16,24
  display.flipScreenVertically(); 

 
  // override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, LORA_DEFAULT_DIO0_PIN);// set CS, reset, IRQ pin
 
  if(!LoRa.begin(915E6)){             // initialize ratio at 915 MHz
    Serial.println("INICIALIZAÇÃO LORA DO SLAVE NÃO FOI ESTABELECIDA");
    while (true);                       // if failed, do nothing
  }
  Serial.println("INICIANDO SLAVE LORA");
}
 
void loop(){
<<<<<<< HEAD
  onReceive(LoRa.parsePacket()); //analise um pacote e chama onReceive com o resultado
  if(((millis()>intervaloSemLoRa+10000) && (RedeON))||((millis() > intervaloSemLoRa+60000)&&(!RedeON)))ESP.restart();
=======
  onReceive(LoRa.parsePacket()); //analise um pacote e chama onReceive com o resultado:
  if(lastSendTimeOLED  + 500 < millis()){
    Serial.println( millis());
    digitalWrite(16,digitalRead(0));
    displayelogica(sender,recipient,incoming);
    lastSendTimeOLED  = millis();
  }
  
  
>>>>>>> 108c3ec33b59e7d4a351f423cd137c2a34a45eb5
}
 
void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(Master);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}
 
void onReceive(int packetSize){
  if(packetSize == 0) return;          // if there's no packet, return
<<<<<<< HEAD
  
  intervaloSemLoRa = millis();
  RedeON = 1;

  // read packet header bytes:
  int recipient       = LoRa.read();     // recipient address
  byte sender         = LoRa.read();     // sender address
  byte incomingMsgId  = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();     // incoming msg length
  String incoming = "";
=======

  // read packet header bytes:
  recipient = LoRa.read();          // recipient address
  sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  incoming = "";
>>>>>>> 108c3ec33b59e7d4a351f423cd137c2a34a45eb5
 
  while(LoRa.available())incoming += (char)LoRa.read();
 
  if(incomingLength != incoming.length()){   // check length for error
    Serial.println("error: message length does not match length");
    return;                                  // skip rest of function
  }



  if(recipient == localAddress){
    if(incoming == "1RELE1"){
      digitalWrite(RELE1,1);
      sendMessage("OK1RELE1");
    }else if(incoming == "1RELE0"){
      digitalWrite(RELE1,0);
      sendMessage("OK1RELE0");
    }
    if(incoming == "2RELE1"){
      digitalWrite(RELE2,0);
      sendMessage("OK2RELE1");
    }else if(incoming == "2RELE0"){
      digitalWrite(RELE2,1);
      sendMessage("OK2RELE0");
    }
    if(incoming == "HQ")sendMessage("H" + String((analogRead(divisor1) * 100)/4095));
<<<<<<< HEAD
    if(incoming == "RESET" + String(localAddress)){ESP.restart();}
=======
>>>>>>> 108c3ec33b59e7d4a351f423cd137c2a34a45eb5
  }
 
  // if the recipient isn't this device or broadcast,
  if(recipient != localAddress && recipient != Master){
    Serial.print("MESSAGEM PARA O SLAVE ");
    Serial.println(recipient);
    return;                             // skip rest of function
  }
 
  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: " + sender);
  Serial.println("Sent to: " + recipient);
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
  
  senderSlave = true;
}

void displayelogica(byte sender, int recipient, String incoming){
    display.drawString(0, 0, "IRRIGAÇÃO 4.0      SLAVE");
    display.drawString(0,15, "ADDR: " + String(localAddress));
    display.drawString(60,15, "UMID: " + String((analogRead(divisor1) * 100)/4095) + "%");
<<<<<<< HEAD
    if(sender == 250)display.drawString(0, 30, "MASTER:  " + incoming);
    else display.drawString(0, 30, "SLAVE " + String(sender) + ": " + incoming);
    if(recipient!=localAddress) display.drawString(0, 45, "PARA O SLAVE " + recipient);
=======
    if(sender == 250){
      display.drawString(0, 30, "MASTER:  " + incoming);
    }else{
      display.drawString(0, 30, "SLAVE " + String(sender) + ": " + incoming);
    }

    if(recipient != localAddress){
      display.drawString(0, 45, "PARA O SLAVE " + recipient);
    }
>>>>>>> 108c3ec33b59e7d4a351f423cd137c2a34a45eb5
    else{
      display.drawString(0, 45, "PARA MIM");
      if(senderSlave){
        if(incoming == "HQ"){
          String message = "H" + String((analogRead(divisor1) * 100)/4095);
          sendMessage(message);
          Serial.println("Enviado: " + message);
          //senderSlave = false; 
        }
      }
    }
    display.display();
    display.clear();
 }
