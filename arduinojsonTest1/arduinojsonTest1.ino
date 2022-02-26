#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h> 


bool writeFile(String values, String pathFile, bool appending) {
  char *mode = "w";  //aberto para escrita (cria arquivo se não existir). Exclui o conteúdo e substitui o arquivo.
  if (appending) mode = "a";  //aberto para anexação (cria o arquivo se não existir)
  SPIFFS.begin(true);
  File wFile = SPIFFS.open(pathFile, mode);
  if (!wFile) {
    Serial.println("- Falha ao escrever na pasta.");
    return false;
  } else {
    wFile.println(values);
    //Serial.println(values);
    Serial.println("- Gravado!");
  }
  wFile.close();
  return true;
}

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
  
  return values;
}

void setup() {
  Serial.begin(9600);
  
  StaticJsonDocument<2560> doc;
  String input = readFile("/addr.json");
  Serial.println(input);
  deserializeJson(doc, input);
  //Serial.println(doc);

  const char* sensor = doc[0]["hora"];
  float lat = doc[0]["duracao"];
  float lon = doc[0]["addr"];

  Serial.println("-***-*-*--*-*-*-**-**-*-*-*-*-----***");
  Serial.println(sensor);
  Serial.println(lat);
  Serial.println(lon);/**/
  doc[0]["hora"]= "10:00";
  String gravaJson = "";
  serializeJson(doc,gravaJson);
  writeFile(gravaJson,"/addr.json",false);
}

void loop() {
  

}
