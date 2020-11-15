#ifndef _LED_H
#define _LED_H
#include <Adafruit_NeoPixel.h>
#include <vector>

#define snakeLength 1
class WS2811LED
{
    public:
    enum MODE
    {
        TRAILING,
        BREATH,
        SNAKE,
        SNAKE2,
        SNAKE3,
        TETRIS,
        DOT,
        RAINBOW,
        RAINBOW2
        
    };
    private:
    Adafruit_NeoPixel *strip = 0;
    std::vector<uint32_t> colors;
    uint8_t _mode =  RAINBOW2;
    uint16_t _leds = 0;
    uint16_t _speed = 70;
    void Trailing();
    void Breath();
    void Snake();
    void Snake2();
    void Snake3();
    void Tetris();
    void Dot();
    void Rainbow();
    void Rainbow2();
    public:
    WS2811LED(uint16_t LedCount,uint8_t PIN = 5,uint8_t colorCount = 1);
    void exec();
    void setState(uint8_t& mode);
    void setColor(uint8_t i= 0,uint32_t color = 0x00000000);
    void setSpeed(uint16_t speed);
};
#endif