#include "App.h"

WebServer::WebServer(uint16_t port)
{
    this->server = new AsyncWebServer(port);
}
WS2811LED *Socket::_strip = 0;
void WebServer::setStaticFilePath(const char *url)
{
    this->server->serveStatic(url, LittleFS, "/", "max-age:86400");
}

void WebServer::config()
{
    Serial.println("START SERVER");
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("Client GET Request");
        request->send(LittleFS, "/index.html", "text/html");
    });
    server->onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/html", "<html><head><title>404: NOT FOUND</title></head></html>");
    });
}

void WebServer::Begin(Socket *socket)
{
    
    server->addHandler(socket->getSocket());
    
    LittleFS.begin();
    config();
    server->begin();
}

AsyncWebSocket *Socket::getSocket()
{
    return this->socket;
}
Socket::Socket(const String &url)
{
    this->socket = new AsyncWebSocket(url);
    socket->onEvent(this->onEvent);
}

void Socket::attachWS2811(WS2811LED *strip)
{
    _strip = strip;
}
void Socket::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{

    if (type == WS_EVT_CONNECT)
    {
        Serial.println("Client");
    }
    if (type == WS_EVT_DATA)
    {
        DataEventHandler(client, type, (AwsFrameInfo *)arg, data, len);
    }
}

void Socket::DataEventHandler(AsyncWebSocketClient *client, AwsEventType type, AwsFrameInfo *info, uint8_t *data, size_t len)
{
    //Single frame message
    if (info->final && info->index == 0 && info->len == len)
    {
        if (info->opcode == WS_TEXT)
        {
            Serial.println("Wrong type of message: message supose to be 4 byte 1 mode and 3 color");
        }
        else
        {
            // byte 0: mode
            // byte 1,2: speed
            // byte 3: number of colors
            // byte n*byte3: colors

            _strip->setState(data[0]);
            uint16_t speed;
            memcpy(&speed, data + 1, 2);
            _strip->setSpeed(speed);
            data += 4;
            uint32_t color =0x0| (uint32_t)data[2] <<16|(uint32_t)data[0]<<8|(uint32_t)data[1];
            Serial.println(color,HEX);
            _strip->setColor(0,color);
            Serial.println();
        }
    }
}