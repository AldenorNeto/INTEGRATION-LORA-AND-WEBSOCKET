//Incluindo as bibliotecas necessárias
#include <Wire.h> 
#include "SSD1306.h"

int A0Normalizado;
byte localAddress = 0xb1;  

SSD1306 display(0x3c, 4, 15, 16); //Cria e ajusta o Objeto display

void setup(){
  pinMode(A0,INPUT);

  display.init();
  display.setFont(ArialMT_Plain_10); //10,16,24
  display.setTextAlignment(TEXT_ALIGN_LEFT);

}
void loop(){

  
  A0Normalizado = (analogRead(A0) * 100)/4095;
  display.drawString(0, 0, "IRRIGAÇÃO 4.0");
  display.drawString(0,15, "ADDR: " + String(localAddress));
  display.drawString(60, 15, "UMID: " + String(A0Normalizado) + "%");
  
  display.display();
  delay(100);
  display.clear();
  delay(100);
}
