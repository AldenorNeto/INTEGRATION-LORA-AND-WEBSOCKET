/********************************************************
 * CANAL INTERNET E COISAS
 * ESP32 - Utilizacao do SPIFFS
 * 11/2019 - Andre Michelon
*********************************************************/

// Bibliotecas ------------------------------------------
#include <SPIFFS.h>

// Setup ------------------------------------------------
void setup(){
  /*Serial.begin(115200);

  // --- Inicializando SPIFSS ---
  Serial.println("\nInicializando SPIFSS ---------------------");
  if (SPIFFS.begin()) {
    Serial.println("Ok");
  } else {
    Serial.println("Falha");
    while(true);
  }
  
  // --- Informacoes sobre SPIFSS ---
  Serial.println("\nInformacoes ------------------------------");
  Serial.printf("totalBytes: %u\nusedBytes: %u\nfreeBytes: %u\n",
                  SPIFFS.totalBytes(),
                  SPIFFS.usedBytes(),
                  SPIFFS.totalBytes() - SPIFFS.usedBytes());

  // --- Listagem de arquivos ---
  Serial.println("\nArquivos ---------------------------------");

  if (!SPIFFS.exists("/Imagem.jpg")) {
    Serial.println("Arquivo '/Imagem.jpg' inexistente");
  }

  File dir = SPIFFS.open("/Log");
  File file = dir.openNextFile();
  while (file) {
    Serial.printf(" %s - %u bytes\n", file.name(), file.size());
    file = dir.openNextFile();
  }

  // --- Gravando arquivo ---
  file = SPIFFS.open("/Log/Log.txt", "a");
  
  delay(1);
  
  if (file) {
    file.println("Inicializando...");
    file.printf("Registro %u\r\n", millis());
    file.close();
  }

  // --- Lendo arquivo ---
  Serial.println("\nLendo Arquivo ----------------------------");
  file = SPIFFS.open("/Log/Log.txt", "r");

  if (file) {
    Serial.printf("Nome: %s - %u bytes\n", file.name(), file.size());
    while (file.available()){
      Serial.println(file.readStringUntil('\n'));
    }
    file.close();
  }

  // --- Excluindo arquivo ---
  /*Serial.println("\nExcluindo Arquivo ----------------------------");
  if (SPIFFS.remove("/Log/Log.txt")) {
    Serial.println("Arquivo '/Log/Log.txt' excluido");
  } else {
    Serial.println("Exclusão '/Log/Log.txt' falhou");
  }*/
}

void loop() {
}
