#include <FS.h>
#include <SPIFFS.h> 
#include <WiFi.h>
#include <HTTPClient.h>
  
const char* ssid     = "Grendene.Coletores";
const char* password = "ISO8804650216900479";


String readFile(String pathFile){
  Serial.println("- Lendo: " + pathFile);
  SPIFFS.begin(true);
  File rFile = SPIFFS.open(pathFile, "r");
  String values;
  if (!rFile) Serial.println("- Failed to open file.");
  else while (rFile.available()) values += rFile.readString();
  rFile.close();
  Serial.println(values);
  return values;
}


void setup() {
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
  pinMode(0,INPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

    //  String gravaJson = "[{\"addr\":\"1\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000111\"},{\"addr\":\"2\",\"duracao\":\"3\",\"hora\":\"23:32\",\"s\":\"0110000\"},{\"addr\":\"3\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"4\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"5\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"6\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"7\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"8\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"9\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"10\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"11\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"12\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"13\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"14\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"15\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"16\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"17\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"18\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"19\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"20\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"21\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"22\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"23\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"24\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"},{\"addr\":\"25\",\"duracao\":\"1\",\"hora\":\"00:00\",\"s\":\"0000000\"}]";
   // writeFile(gravaJson,"/addr.json",false);
}

 
void loop() {
  
  if (!digitalRead(0)){ //Check the current connection status
  
    HTTPClient http;

    http.begin("https://na1.ai.dm-us.informaticacloud.com/active-bpel/public/rt/gKlSdumC0iIjZgAY6sxzAX/p_CALL_SAVE_JSON"); //Specify the URL
    http.addHeader("Content-Type", "application/json"); 
    String input = readFile("/addr.json");
    //String memoria = "{\"json\":\"[{'addr':'0','txt':'jard esqrd fab 03','duracao':'3','hora':'01:47','s':'0111111'},{'addr':'1','txt':'fab 01','duracao':'5','hora':'00:32','s':'0111000'},{'addr':'2','txt':'fab 02','duracao':'2','hora':'00:47','s':'0101010'},{'addr':'3','txt':'fab 03','duracao':'2','hora':'04:00','s':'0111001'},{'addr':'4','txt':'fab 04','duracao':'5','hora':'04:00','s':'0101001'},{'addr':'5','txt':'','duracao':'4','hora':'04:00','s':'0111001'},{'addr':'6','txt':'','duracao':'5','hora':'04:00','s':'0101000'},{'addr':'7','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'8','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'9','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'10','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'11','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'12','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'13','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'14','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'15','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'16','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'17','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'18','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'19','txt':'','duracao':'1','hora':'00:00','s':'0000000'},{'addr':'20','txt':'','duracao':'1','hora':'00:00','s':'0000000'}] \"}" ;
    input.replace("\"", "\\\"");
    input[input.length() - 1] = ' ';
    String memoria = "{\"json\":\"" + input + "\"}";
    Serial.println(memoria);
    int httpCode = http.POST(memoria);
  
    if(httpCode > 0){ //Check for the returning code
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
    else{
      Serial.println("Error on HTTP request");
    }
    http.end(); //Free the resources
  }

  
}
