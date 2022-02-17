#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid     = "Redmi 10";
const char* password = "bolsonaro";
char jsonOutput[128];
  
void setup() {
  
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected to the WiFi network ");
  Serial.println(ssid);
}
  
void loop() {
  
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
   HTTPClient http;   
  
   http.begin("http://ptsv2.com/t/90ul9-1645026328");  //Specify destination for HTTP request
   http.addHeader("Content-Type", "text/plain");             //Specify content-type header


   const size_t CAPACITY = JSON_OBJECT_SIZE(1);
   StaticJsonDocument<CAPACITY> doc;

   JsonObject object = doc.to<JsonObject>();
   object["json"] = "{\"device\":\"esp32-CC50E39613DC\",\"estado\":\"acionado\"}";
   serializeJson(doc,jsonOutput);
   
   Serial.println(String(jsonOutput));
  
   int httpResponseCode = http.POST(String(jsonOutput));   //Send the actual POST request
  
  if(httpResponseCode>0){
  
    String response = http.getString();                       //Get the response to the request
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response); 

    http.end(); 
   }else{
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
   }
   
 }else{
    Serial.println("Error in WiFi connection");   
 }
  delay(10000);  //Send a request every 10 seconds
}
