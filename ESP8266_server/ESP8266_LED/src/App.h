#ifndef _APP_H
#define _APP_H
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <iostream>
#include "LED.h"



class Socket
{
    private:
    AsyncWebSocket *socket;
    static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    static void DataEventHandler(AsyncWebSocketClient *client, AwsEventType type, AwsFrameInfo *info, uint8_t *data, size_t len);
    static WS2811LED* _strip;
    public:
    Socket(const String& url);
    void attachWS2811(WS2811LED* strip);
    AsyncWebSocket *getSocket();
};

class WebServer
{
    private:
        AsyncWebServer *server;
        
        void config();
    public:
    WebServer(uint16_t port);
    void Begin(Socket* Socket);
    void setStaticFilePath(const char* url);
};
#endif