//Incluindo as bibliotecas necessárias
#include <Wire.h> 
#include "SSD1306.h"






SSD1306 display(0x3c, 4, 15, 16); //Cria e ajusta o Objeto display

void setup()
{

  //O estado do GPIO16 é utilizado para controlar o display OLED

  //Reseta as configurações do display OLED

  //Para o OLED permanecer ligado, o GPIO16 deve permanecer HIGH
  //Deve estar em HIGH antes de chamar o display.init() e fazer as demais configurações,
  //não inverta a ordem


  display.init();
  display.setFont(ArialMT_Plain_10); //10,16,24
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setLogBuffer(5, 30);
}

void loop(){
  
  display.clear(); //limpa tela
  
  display.println("NovTec"); 
  display.drawLogBuffer(92, 54);
  display.display();

}
