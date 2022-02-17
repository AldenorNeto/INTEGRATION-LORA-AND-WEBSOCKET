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
  Serial.println("Connected to the WiFi network");
}

void loop() {
  
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
   HTTPClient http;   
  
   http.begin("http://jsonplaceholder.typicode.com/posts");  //Specify destination for HTTP request
   http.addHeader("Content-Type", "text/plain");             //Specify content-type header


   const size_t CAPACITY = JSON_OBJECT_SIZE(1);
   StaticJsonDocument<CAPACITY> doc;

   JsonObject object = doc.to<JsonObject>();
   object["title"] = "Brasileiro";

   serializeJson(doc,jsonOutput);
   
   Serial.println(String(jsonOutput));
   
   int httpCode = http.POST(String(jsonOutput));

  if(httpCode>0){
    
    String response = http.getString(); 
    
    Serial.println(httpCode);   //Print return code
    Serial.println(response);
    http.end(); 
   }else{
    Serial.print("Error on sending POST: ");
 
   }
   
 }else{
    Serial.println("Error in WiFi connection");   
 }
  delay(10000);  //Send a request every 10 seconds
}
