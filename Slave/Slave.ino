//////SLAVE
#include <SPI.h>              // include libraries
#include <LoRa.h>
 
const int csPin = 18;          // LoRa radio chip select
const int resetPin = 14;       // LoRa radio reset
 
String outgoing;              // outgoing message
bool senderSlave = false;
 
byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0x02;     // address of this device
byte destination = 0x05;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 2000;          // interval between sends
 
void setup() {
  Serial.begin(9600);                   // initialize serial
  while (!Serial);
 
  // override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, LORA_DEFAULT_DIO0_PIN);// set CS, reset, IRQ pin
 
  if (!LoRa.begin(915E6)) {             // initialize ratio at 915 MHz
    Serial.println("INICIALIZAÇÃO LORA DO SLAVE NÃO FOI ESTABELECIDA");
    while (true);                       // if failed, do nothing
  }
 
  Serial.println("INICIANDO SLAVE LORA");
}
 
void loop() {
  if (senderSlave) {
    String message = String(analogRead(38));   // send a message
    sendMessage(message);
    Serial.println("Enviado: " + message);
    senderSlave = false;
  }
 
  //analise um pacote e chama onReceive com o resultado:
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
 
  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }
 
  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("MESSAGEM PARA OUTRO SLAVE");
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
