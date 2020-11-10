#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

//======Global init==================
static AsyncWebServer Server(3000);
static AsyncWebSocket Socket("/socket");

const char *ssid = "Hoang Vu";
const char *password = "05112001";
//===================================
void ConfigServer();
void SocketEventHandler(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

bool StartWifi(const char *ssid, const char *password, uint8_t mode);
void setup()
{
  LittleFS.begin();
  Serial.begin(115200);
  if(StartWifi(ssid,password,1))
  {
    Serial.println("Connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Socket.onEvent(SocketEventHandler);
    ConfigServer();
  }
  else
  {
    Serial.println("failed to connect");
  }
  
}

void loop()
{
}

bool StartWifi(const char *ssid, const char *password, uint8_t mode)
{
  switch (mode)
  {
  case 0:
    WiFi.softAP(ssid, password, 1, false, 1);
    return true;
    break;
  case 1:
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    return WiFi.waitForConnectResult() == WL_CONNECTED;
    break;
  default:
    return false;
    break;
  }
}

void ConfigServer()
{
  Server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(200, "text/html", "");
    request->send(LittleFS,"/index.html","text/html");
  });
  Server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/html", "<html><head><title>404: NOT FOUND</title></head></html>");
  });
  Server.addHandler(&Socket);
  Server.begin();
}

void SocketEventHandler(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
  case WS_EVT_DISCONNECT:
    Serial.println("Disconnected");
    client->close();
    break;
  case WS_EVT_CONNECT:
    Serial.println("Connected");
    break;

  default:
    break;
  }
}