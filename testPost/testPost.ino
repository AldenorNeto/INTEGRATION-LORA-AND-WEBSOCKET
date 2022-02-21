
#include <WiFi.h>
#include <HTTPClient.h>
  
const char* ssid     = "Redmi 10";
const char* password = "bolsonaro";
  
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
  
    http.begin("https://na1.ai.dm-us.informaticacloud.com/active-bpel/public/rt/gKlSdumC0iIjZgAY6sxzAX/p_CALL_SAVE_JSON"); //Specify the URL
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
    int httpCode = http.POST();                                        //Make the request
  
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
