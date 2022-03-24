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
  delay(400);
  WiFi.begin(ssid, password);
  pinMode(0,INPUT);
  while (WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

 
void loop() {
  
  if (!digitalRead(0)){ //Check the current connection status
    HTTPClient http;
    http.begin("https://na1.ai.dm-us.informaticacloud.com/active-bpel/public/rt/gKlSdumC0iIjZgAY6sxzAX/p_CALL_SAVE_JSON"); //Specify the URL
    http.addHeader("Content-Type", "application/json"); 
    String input = readFile("/addr.json");
    input.replace("\"", "\\\"");
    Serial.println(input);
    input[input.length()-1] = ' ';
    input[input.length()-2] = ' ';
    input = "{\"json\":\"" + input + "\"}";
    int httpCode = http.POST(input);
    Serial.println(String(httpCode) + ": " + String(http.getString()));
    http.end(); //Free the resources
  }

}
