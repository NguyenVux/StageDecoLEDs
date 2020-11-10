#include <ESP8266WiFi.h>  
#include <WebSocketsServer.h>      
#include <ESP8266WebServer.h>

const char *ssid = "DMX"; 
const char *password = "123456789";  
ESP8266WebServer server(80);  
WebSocketsServer WebSocket(81);

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  if(!WiFi.softAP(ssid, password,1,false,1))
  {
    Serial.println("Unable to start access point");
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    
  }   
  else
  {
    Serial.print("Access Point \"");
    Serial.print(ssid);
    Serial.println("\" started");
    Serial.print("IP address:\t");
    Serial.println(WiFi.softAPIP());
    
    WebSocket.begin();
    WebSocket.onEvent(SocketEvent);
    startServer();
  }
        

}

void loop() { 
  server.handleClient();  
}

void startServer()
{
  server.on("/edit.html",  HTTP_GET, []() {  // If a POST request is sent to the /edit.html address,
    server.send(200, "text/plain", "k"); 
  });  
  server.onNotFound([](){
      server.send(404, "text/plain", "404: File Not Found");
    });

    
  server.begin();
}

void SocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
  switch(type)
  {
    case WStype_DISCONNECTED:
    break;
  }
}
