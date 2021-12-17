#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SPI.h>

int timeZone = -2;

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


#define LED LED_BUILTIN
#define SW     23

const char* ssid     = "Grendene.Coletores";
const char* password = "ISO8804650216900479";

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

int indice = 1;

String duracao1 = "0";
String hora1 = "00:00";
String s1_0 = "0000000";
String umidade1;
String bomba1;

String duracao2 = "0";
String hora2 = "00:00";
String s2_0 = "0000000";
String umidade2;
String bomba2;

String duracao3 = "0";
String hora3 = "00:00";
String s3_0 = "0000000";
String umidade3;
String bomba3;

String duracao4 = "0";
String hora4 = "00:00";
String s4_0 = "0000000";
String umidade4;
String bomba4;

String duracao5 = "0";
String hora5 = "00:00";
String s5_0 = "0000000";
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
    


    if(var == "DURACAO2"){
          duracao2 = val;
    }
    if(var == "HORA2"){
          hora2 = val;
    }
    if(var == "S2_0"){
          s2_0 = val;
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
    


    if(var == "DURACAO4"){
          duracao4 = val;
    }
    if(var == "HORA4"){
          hora4 = val;
    }
    if(var == "S4_0"){
          s4_0 = val;
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

  }
}


void setup(){
 
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(A0, INPUT);
  
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
        NULL,                      //prioridade
        NULL,                   //Não precisamos de referência para a tarefa
        0);
        
}

void setupNTP(){
  
    //Inicializa o client NTP
    ntpClient.begin();
    
    //Espera pelo primeiro update online
    Serial.println("Waiting for first update");
    while(!ntpClient.update())
    {
        Serial.print(".");
        ntpClient.forceUpdate();
        delay(500);
    }

    Serial.println();
    Serial.println("First Update Complete");
}

void wifiConnectionTask(void* param){
  
    while(true){
      
        //Se a WiFi não está conectada
        if(WiFi.status() != WL_CONNECTED)
        {
            //Manda conectar
            connectWiFi();
        }

        //Delay de 100 ticks
        vTaskDelay(100);
    }
}
void connectWiFi()
{
    Serial.println("Connecting");

    //Troque pelo nome e senha da sua rede WiFi
    WiFi.begin("Grendene.Coletores", "ISO8804650216900479");
    
    //Espera enquanto não estiver conectado
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
}



void loop() {

  Date date = getDate();
  webSocket.loop(); server.handleClient();

  Serial.printf("%01d\n",date.dayOfWeek);
  Serial.printf("%02d %02d\n",date.day, date.month);
  Serial.printf("%02d %02d\n",date.hours, date.minutes);
 
  static unsigned long l = 0;
  unsigned long t = millis();
 
  if((t-l) > 1000){
   
    umidade1 = String(analogRead(A0));
    umidade2 = String(analogRead(A0));
    umidade3 = String(analogRead(A0));
    umidade4 = String(analogRead(A0));
    umidade5 = String(analogRead(A0));


    JSONtxt = "{\"INDICE\":\""+String(indice)+"\",";
    if(indice == 1){
      JSONtxt += "\"DURACAO1\":\""+duracao1+"\",";
      JSONtxt += "\"HORA1\":\""+hora1+"\",";
      JSONtxt += "\"S1_0\":\""+s1_0+"\",";
      JSONtxt += "\"UMIDADE1\":\""+umidade1+"\",";
      JSONtxt += "\"BOMBA1\":\""+bomba1+"\"}";
      indice = 2;
    }

    else if(indice == 2){
      JSONtxt += "\"DURACAO2\":\""+duracao2+"\",";
      JSONtxt += "\"HORA2\":\""+hora2+"\",";
      JSONtxt += "\"S2_0\":\""+s2_0+"\",";
      JSONtxt += "\"UMIDADE2\":\""+umidade2+"\",";
      JSONtxt += "\"BOMBA2\":\""+bomba2+"\"}";
      indice = 3;
    }

    else if(indice == 3){
      JSONtxt += "\"DURACAO3\":\""+duracao3+"\",";
      JSONtxt += "\"HORA3\":\""+hora3+"\",";
      JSONtxt += "\"S3_0\":\""+s3_0+"\",";
      JSONtxt += "\"UMIDADE3\":\""+umidade3+"\",";
      JSONtxt += "\"BOMBA3\":\""+bomba3+"\"}";
      indice = 4;
    }
    
    else if(indice == 4){
      JSONtxt += "\"DURACAO4\":\""+duracao4+"\",";
      JSONtxt += "\"HORA4\":\""+hora4+"\",";
      JSONtxt += "\"S4_0\":\""+s4_0+"\",";
      JSONtxt += "\"UMIDADE4\":\""+umidade4+"\",";
      JSONtxt += "\"BOMBA4\":\""+bomba4+"\"}";
      indice = 5;
    }
    
    else if(indice == 5){
      JSONtxt += "\"DURACAO5\":\""+duracao5+"\",";
      JSONtxt += "\"HORA5\":\""+hora5+"\",";
      JSONtxt += "\"S5_0\":\""+s5_0+"\",";
      JSONtxt += "\"UMIDADE5\":\""+umidade5+"\",";
      JSONtxt += "\"BOMBA5\":\""+bomba5+"\"}";
      indice = 1;
    }
    

    Serial.println(JSONtxt);
    webSocket.broadcastTXT(JSONtxt);
   
  }

  
}

Date getDate()
{
    //Recupera os dados de data e horário usando o client NTP
    char* strDate = (char*)ntpClient.getFormattedDate().c_str();

    //Passa os dados da string para a struct
    Date date;
    sscanf(strDate, "%d-%d-%dT%d:%d", 
                    &date.year, 
                    &date.month, 
                    &date.day, 
                    &date.hours, 
                    &date.minutes);

    //Dia da semana de 0 a 6, sendo 0 o domingo
    date.dayOfWeek = ntpClient.getDay();
    return date;
}
