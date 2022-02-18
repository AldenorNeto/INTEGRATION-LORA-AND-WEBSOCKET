
#include <WiFi.h>
#include <HTTPClient.h>
  
const char* ssid     = "Grendene.Coletores";
const char* password = "ISO8804650216900479";
  
void setup() {
  
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
  
}
  
void loop() {
  
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
  
    HTTPClient http;
  
    http.begin("https://10.2.4.229:7443/process-engine/public/rt/p_SAVE_CSV?device=esp32-CC50E39613DC&estado=acionado"); //Specify the URL
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
    int httpCode = http.GET();                                        //Make the request
  
    if (httpCode > 0) { //Check for the returning code
  
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
  
    else {
      Serial.println("Error on HTTP request");
    }
  
    http.end(); //Free the resources
  }
  
  delay(5000);
  
}
