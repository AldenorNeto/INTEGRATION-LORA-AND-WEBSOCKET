#include <FS.h>     //File System [ https://github.com/espressif/arduino-esp32/tree/master/libraries/FS ]
#include <SPIFFS.h> 

String semana = "1110111";
String json = "5454 ";
  
void setup() {
  int t = 1000;

  Serial.begin(9600);
  delay(t);

  readFile("/addr.json");
  delay(t);
  Serial.println(json);
  for (int i=0; i < semana.length(); i++){
    json[93+i] = semana[i];
  }
  Serial.println("...................................................");
  Serial.println(json);
  writeFile(json,"/addr.json", false );
  
}

void loop() {}

/*--- ESCREVE O ARQUIVO ---*/
bool writeFile(String values, String pathFile, bool appending) {
  char *mode = "w"; //open for writing (creates file if it doesn't exist). Deletes content and overwrites the file.
  if (appending) mode = "a"; //open for appending (creates file if it doesn't exist)
  Serial.println("- Writing file: " + pathFile);
  Serial.println("- Values: " + values);
  SPIFFS.begin(true);
  File wFile = SPIFFS.open(pathFile, mode);
  if (!wFile) {
    Serial.println("- Failed to write file.");
    return false;
  } else {
    wFile.println(values);
    Serial.println("- Written!");
  }
  wFile.close();
  return true;
}

/*--- LEITURA DO ARQUIVO ---*/
String readFile(String pathFile) {
  Serial.println("- Reading file: " + pathFile);
  SPIFFS.begin(true);
  File rFile = SPIFFS.open(pathFile, "r");
  String values;
  if (!rFile) {
    Serial.println("- Failed to open file.");
  } else {
    while (rFile.available()) {
      values += rFile.readString();
    }
    Serial.println("- File values: " + values);
  }
  rFile.close();
  json = values;
  return values;
}

/*--- APAGA O ARQUIVO ---*/
bool deleteFile(String pathFile) {
  Serial.println("- Deleting file: " + pathFile);
  SPIFFS.begin(true);
  if (!SPIFFS.remove(pathFile)) {
    Serial.println("- Delete failed.");
    return false;
  } else {
    Serial.println("- File deleted!");
    return true;
  }
}

/*--- RENOMEIA O ARQUIVO ---*/
void renameFile(String pathFileFrom, String pathFileTo) {
  Serial.println("- Renaming file " + pathFileFrom + " to " + pathFileTo);
  SPIFFS.begin(true);
  if (!SPIFFS.rename(pathFileFrom, pathFileTo)) {
    Serial.println("- Rename failed.");
  } else {
    Serial.println("- File renamed!");
  }
}

/*--- FORMATA O FILE SYSTEM ---*/
bool formatFS() {
  Serial.println("- Formatting file system...");
  SPIFFS.begin(true);
  if (!SPIFFS.format()) {
    Serial.println("- Format failed.");
    return false;
  } else {
    Serial.println("- Formatted!");
    return true;
  }
}

/*--- LISTA OS ARQUIVOS DOS DIRETÓRIOS ---*/
void listFiles(String path) {
  Serial.println("- Listing files: " + path);
  SPIFFS.begin(true);
  File root = SPIFFS.open(path);
  if (!root) {
    Serial.println("- Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("- Not a directory: " + path);
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("- Dir: ");
      Serial.println(file.name());
    } else {
      Serial.print("- File: ");
      Serial.print(file.name());
      Serial.print("\tSize: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}
