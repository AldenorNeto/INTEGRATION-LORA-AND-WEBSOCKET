#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h> 

String readFile(String pathFile){
  Serial.println("- Lendo: " + pathFile);
  SPIFFS.begin(true);
  File rFile = SPIFFS.open(pathFile, "r");
  String values;
  if (!rFile) {
    Serial.println("- Failed to open file.");
  } else {
    while (rFile.available()) {
      values += rFile.readString();
    }
  }
  rFile.close();
  Serial.println(" - - - - - - ======> values");
  Serial.println(values);
  return values;
}

void setup() {
  Serial.begin(9600);
  
  StaticJsonDocument<256> doc;
  doc = readFile("/addr.json");

  
  //deserializeJson(doc, input);
  //Serial.println(doc);

  const char* sensor = doc[3]["hora"];
  long time = doc["time"];
  float lat = doc["data"][0];
  float lon = doc["data"][1];

  Serial.println(sensor);
  Serial.println("-***-*-*--*-*-*-**-**-*-*-*-*-----***");
  Serial.println(lat,3);
  Serial.println(lon,2);
}

void loop() {
  

}
