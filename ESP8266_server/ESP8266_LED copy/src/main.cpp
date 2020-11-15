#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Adafruit_NeoPixel.h>

#define maxLed 50
#define NeoPixelPin 5
//======Global init==================
static AsyncWebServer Server(80);
static AsyncWebSocket Socket("/socket");
static Adafruit_NeoPixel strip = Adafruit_NeoPixel(maxLed, NeoPixelPin, NEO_RGB + NEO_KHZ800);
// const char *ssid = "HCMUS-F203";
// const char *password = "phonghoc@f203";

const char *ssid = "Hoang Vu";
const char *password = "05112001";

// const char *ssid = "DMX_IO";
// const char *password = "123456789";

uint8_t color[3] = {255, 0, 0};
uint8_t CurrPixel = 0;
//=========Enumeration===============

enum LedMode
{
  TRAILING,
  BREATH,
  SNAKE,
  MUSIC
};

uint8_t Mode = TRAILING;

//===================================
void ConfigServer();
void SocketEventHandler(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void DataEvent(AsyncWebSocketClient *client, void *arg, uint8_t *data, size_t len);
int StartWifi(const char *ssid, const char *password, uint8_t mode);
void setup()
{
  LittleFS.begin();
  Serial.begin(115200);
  switch (StartWifi(ssid, password, 1))
  {
  case 1:
    Serial.println("Connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Socket.onEvent(SocketEventHandler);
    ConfigServer();
    break;
  case 0:
    Serial.println("Connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
    Socket.onEvent(SocketEventHandler);
    ConfigServer();
    break;
  default:
    Serial.println("failed to connect");
  }

  strip.begin();
  strip.clear();
  strip.show();
  pinMode(5, OUTPUT);
}

void fillLed(uint8_t index, uint8_t color[]);
void Trailing();
void Breath();
void Snake();
void loop()
{
  switch (Mode)
  {
  case TRAILING:
    Trailing();
    break;
  case BREATH:
    Breath();
    break;
  case SNAKE:
    Snake();
    break;
  default:
    break;
  }
}

int StartWifi(const char *ssid, const char *password, uint8_t mode)
{
  switch (mode)
  {
  case 0:
    WiFi.softAP(ssid, password, 1, false, 1);
    return 0;
    break;
  case 1:
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() == WL_CONNECTED)
    {
      return 1;
    }
    return -1;
    break;
  default:
    return -1;
    break;
  }
}

void ConfigServer()
{
  Server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    //request->send(200, "text/html", "");
    request->send(LittleFS, "/index.html", "text/html");
  });
  Server.serveStatic("/files", LittleFS, "/", "max-age=86400");
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
    client->printf("Confirm Connection");
    Serial.println("Connected");
    break;
  case WS_EVT_DATA:
    DataEvent(client, arg, data, len);
    break;
  default:
    break;
  }
}

void DataEvent(AsyncWebSocketClient *client, void *arg, uint8_t *data, size_t len)
{
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len)
  {
    //the whole message is in a single frame and we got all of it's data
    if (info->opcode == WS_TEXT)
    {
      Serial.println("Wrong type of message: message supose to be 4 byte 1 mode and 3 color");
    }
    else
    {
      if (info->len != 4)
      {
        Serial.println("Wrong Type of binary buffer");
      }
      else
      {
        Mode = data[0];
        if (memcmp(color, data + 1, 3) != 0)
        {

          memcpy(color, data + 1, 3);
          if(Mode != BREATH)
          fillLed(CurrPixel, color);
          else
          fillLed(maxLed, color);
        }
        
      }
    }
  }
  else
  {
  }
}

void fillLed(uint8_t index, uint8_t color[])
{
  for (uint8_t i = 0; i <= index; ++i)
  {
    strip.setPixelColor(i, color[2], color[0], color[1]);
  }
}

//==================================
void Trailing()
{
  CurrPixel = 0;
  strip.clear();
  for (; CurrPixel < maxLed; ++CurrPixel)
  {
    if (Mode != TRAILING)
    {
      strip.clear();
      strip.show();
      return;
    }
    strip.setPixelColor(CurrPixel, color[2], color[0], color[1]);
    strip.show();
    delay(70);
  }
}
void Snake()
{
  CurrPixel = 0;

  for (; CurrPixel < maxLed; ++CurrPixel)
  {
    if (Mode != SNAKE)
    {
      strip.clear();
      strip.show();
      return;
    }
    strip.clear();
    strip.setPixelColor(CurrPixel, color[2], color[0], color[1]);
    strip.show();
    delay(70);
  }
}
void Breath()
{
  //uint8_t brightness = 0;
  for (short i = 0; i < 256; ++i)
  {
    if(Mode != BREATH) return;
    strip.setBrightness(i);
    delay(70);
  }
  for (short i = 255; i >=0; --i)
  {
    if(Mode != BREATH) return;
    strip.setBrightness(i);
    delay(70);
  }
}
//==================================