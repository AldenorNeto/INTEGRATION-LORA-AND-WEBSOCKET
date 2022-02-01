#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
IPAddress ip(192,168,1,102); // ip in lan
IPAddress gateway(192,168,1,1); // internet access via router
IPAddress subnet(255,255,255,0); //subnet mask
IPAddress myserver(208,104,2,86); // zoomkat web page
EthernetServer server(84); //server port
EthernetClient client;
String readString; 

//////////////////////

void setup(){

  pinMode(4, OUTPUT); //pin selected to control
  Ethernet.begin(mac, ip, subnet, gateway); 
  server.begin();
  Serial.begin(9600); 
  Serial.println("server/client 1.0 test 12/08/11"); // keep track of what is loaded
  Serial.println("Send an g in serial monitor to test client"); // what to do to test client
}

void loop(){
  // check for serial input
  if (Serial.available() > 0) 
  {
    byte inChar;
    inChar = Serial.read();
    if(inChar == 'g')
    {
      sendGET(); // call sendGET function
    }
  }  

  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string 
          readString += c; 
          //Serial.print(c);
        } 

        //if HTTP request has ended
        if (c == '\n') {

          ///////////////
          Serial.println(readString); //print to serial monitor for debuging 

            //now output HTML data header
          if(readString.indexOf('?') >=0) { //don't send new page
            client.println("HTTP/1.1 204 Zoomkat");
            client.println();
            client.println();  
          }
          else {
            client.println("HTTP/1.1 200 OK"); //send new page
            client.println("Content-Type: text/html");
            client.println();

            client.println("<HTML>");
            client.println("<HEAD>");
            client.println("<TITLE>Arduino GET test page</TITLE>");
            client.println("</HEAD>");
            client.println("<BODY>");

            client.println("<H1>Zoomkat's simple Arduino 1.0 button</H1>");

            client.println("<a href=\"/?on\" target=\"inlineframe\">ON</a>"); 
            client.println("<a href=\"/?off\" target=\"inlineframe\">OFF</a>"); 

            //client.println("<IFRAME name=inlineframe src=\"res://D:/WINDOWS/dnserror.htm\" width=1 height=1\">");
            client.println("<IFRAME name=inlineframe style=\"display:none\" >");          
            client.println("</IFRAME>");

            client.println("</BODY>");
            client.println("</HTML>");
          }

          delay(1);
          //stopping client
          client.stop();

          ///////////////////// control arduino pin
          if(readString.indexOf("on") >0)//checks for on
          {
            digitalWrite(4, HIGH);    // set pin 4 high
            Serial.println("Led On");
          }
          if(readString.indexOf("off") >0)//checks for off
          {
            digitalWrite(4, LOW);    // set pin 4 low
            Serial.println("Led Off");
          }
          //clearing string for next read
          readString="";

        }
      }
    }
  }
} 

//////////////////////////
void sendGET() //client function to send/receie GET request data.
{
  if (client.connect(myserver, 80)) {
    Serial.println("connected");
    client.println("GET /~shb/arduino.txt HTTP/1.0");
    client.println();
  } 
  else {
    Serial.println("connection failed");
    Serial.println();
  }

  while(client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) { //connected or data available
    char c = client.read();
    Serial.print(c);
  }

  Serial.println();
  Serial.println("disconnecting.");
  Serial.println("==================");
  Serial.println();
  client.stop();

}
