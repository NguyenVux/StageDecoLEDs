#include <ESP8266WiFi.h>
#include "LED.h"
#include "App.h"

#define PIN 5
WebServer server(80);
Socket socket("/socket");
WS2811LED *strip;
const char *ssid = "DMX_IOT";
const char *password = "123456789";
void setup()
{
  ESP.eraseConfig();
  WiFi.mode(WIFI_AP);
  Serial.begin(115200);
  pinMode(PIN, OUTPUT);
  strip = new WS2811LED(100);
  socket.attachWS2811(strip);
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  //if(WiFi.waitForConnectResult() == WL_CONNECTED)
  if (WiFi.softAP(ssid, password, 5 , false, 1))
  {
    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());
    server.setStaticFilePath("/");
    server.Begin(&socket);
  }
}

void loop()
{
  strip->exec();
}