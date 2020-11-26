#include "LED.h"

WS2811LED::WS2811LED(uint16_t LedCount, uint8_t PIN, uint8_t colorCount)
{
    colors = std::vector<uint32_t>(colorCount);
    strip = new Adafruit_NeoPixel(LedCount, PIN, NEO_RGB + NEO_KHZ800);
    Serial.println("LED ON");
    _leds = LedCount;
    colors[0] = 0xff << 16;
    strip->begin();
    strip->clear();
    strip->setPixelColor(0, colors[0]);
    strip->show();
}

void WS2811LED::exec()
{
    switch (_mode)
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
    case SNAKE2:
        Snake2();
    case SNAKE3:
        Snake3();
        break;
    case TETRIS:
        Tetris();
        break;
    case DOT:
        Dot();
        break;
    case RAINBOW:
        Rainbow();
        break;
    case RAINBOW2:
        Rainbow2();
        break;

    case DOTTED_LINE:
        dotted_line();
        break;

    default:
        break;
    }
}

void WS2811LED::setState(uint8_t &mode)
{
    _mode = mode;
}
void WS2811LED::setColor(uint8_t i, uint32_t color)
{
    if (i > colors.size())
    {
        return;
    }

    for (uint16_t i = 0; i < _leds; i++)
    {
        for (uint32_t c : colors)
        {
            if (strip->getPixelColor(i) == c)
            {
                strip->setPixelColor(i, color);
            }
        }
    }
    colors[i] = color;
}

void WS2811LED::Trailing()
{
    strip->clear();
    for (uint16_t i = 0; i < _leds; ++i)
    {
        if (_mode != TRAILING)
            return;
        strip->setPixelColor(i, colors[0]);
        strip->show();
        delay(_speed);
    }
}
void WS2811LED::Breath()
{
    const uint8_t KEYFRAMES[] = {
        // Rising
        20,
        21,
        22,
        24,
        26,
        28,
        31,
        34,
        38,
        41,
        45,
        50,
        55,
        60,
        66,
        73,
        80,
        87,
        95,
        103,
        112,
        121,
        131,
        141,
        151,
        161,
        172,
        182,
        192,
        202,
        211,
        220,
        228,
        236,
        242,
        247,
        251,
        254,
        255,

        // Falling
        254,
        254,
        251,
        247,
        242,
        236,
        228,
        220,
        211,
        202,
        192,
        182,
        172,
        161,
        151,
        141,
        131,
        121,
        112,
        103,
        95,
        87,
        80,
        73,
        66,
        60,
        55,
        50,
        45,
        41,
        38,
        34,
        31,
        28,
        26,
        24,
        22,
        21,
        20,
        20,
        20,
        20,
        20,
        20,
        20,
        20,
        20,
        20,
        20,
    };

    uint8_t size = sizeof(KEYFRAMES);
    for (uint8_t i = 0; i < size; ++i)
    {
        if (_mode != BREATH)
            return;
        strip->fill(colors[0]);
        strip->setBrightness(KEYFRAMES[i]);
        yield();
        strip->show();
        delay(_speed);
    }
}

void WS2811LED::setSpeed(uint16_t speed)
{
    _speed = speed;
}

void WS2811LED::Snake()
{

    for (uint16_t i = 0; i < _leds; ++i)
    {
        strip->clear();
        if (_mode != SNAKE)
            return;
        strip->setPixelColor(i, colors[0]);
        strip->show();
        yield();
        delay(_speed);
    }
    for (int i = _leds - 1; i >= 0; --i)
    {
        strip->clear();
        if (_mode != SNAKE)
            return;
        strip->setPixelColor(i, colors[0]);
        strip->show();
        yield();
        delay(_speed);
    }
}
void WS2811LED::Snake2()
{

    for (uint16_t i = 0; i < _leds; ++i)
    {
        strip->clear();
        if (_mode != SNAKE2)
            return;
        strip->setPixelColor(i, colors[0]);
        strip->show();
        yield();
        delay(_speed);
    }
}
void WS2811LED::Snake3()
{

    for (uint16_t i = 0; i < _leds; ++i)
    {
        strip->clear();
        if (_mode != SNAKE3)
            return;
        strip->setPixelColor(i, colors[0]);
        strip->setPixelColor(_leds - 1 - i, colors[0]);
        strip->show();
        yield();
        delay(_speed);
    }
}

void WS2811LED::Tetris()
{

    for (uint16 i = 0; i <= _leds; ++i)
    {
        if (_mode != TETRIS)
            return;
        uint16 index = _leds - i;
        for (uint16 k = 0; k < index; ++k)
        {
            if (_mode != TETRIS)
                return;
            strip->clear();
            if (index < _leds)
                strip->fill(colors[0], index);
            strip->setPixelColor(k, colors[0]);
            strip->show();
            yield();
            delay(_speed);
            
        }
    }
}
void WS2811LED::Dot()
{
    const uint16_t size = 3;
    for (uint16_t i = 0; i < _leds; ++i)
    {
        strip->clear();
        if (_mode != DOT)
            return;
        for (int k = i - size; k <= i; ++k)
        {
            if (k >= 0)
                strip->setPixelColor(k, colors[0]);
            yield();
        }
        strip->show();
        delay(_speed);
    }
}
void WS2811LED::Rainbow()
{
    strip->clear();
    for (uint16_t i = 0; i < _leds; ++i)
    {
        if (_mode != RAINBOW)
            return;
        uint16_t hue = map(i, 0, _leds, 0, UINT16_MAX);
        strip->setPixelColor(i, strip->ColorHSV(hue, 255, 255));
        yield();
    }
    strip->show();
    delay(_speed);
}
void WS2811LED::Rainbow2()
{
    strip->clear();
    for (int16_t i = 0; i < _leds; ++i)
    {
        for (uint16_t k = 0; k < _leds; ++k)
        {
            if (_mode != RAINBOW2) return;
            uint16_t hue = map(k, 0, _leds, 0, UINT16_MAX);
            strip->setPixelColor((i+k)%_leds, strip->ColorHSV(hue, 255, 255));
            yield();
        }
        strip->show();
        delay(_speed);
    }
}

void WS2811LED::dotted_line()
{
    uint8_t segmentCount = _leds/(snakeLength+gap);
    for(uint16_t i = 0; true ;++i)
    {
        strip->clear();
        for(int d = 0; d < segmentCount;++d)
        {
            int pos = i-d*(snakeLength+gap);
            pos = pos%_leds+(pos<0)*_leds;
            for(uint8_t k = 0; k < snakeLength;++k )
            {
                if(_mode != DOTTED_LINE)
                {
                    return;
                }
                int pos2 = pos-k;
                pos2 = pos2%_leds+(pos2<0)*_leds;
                strip->setPixelColor(pos2, colors[0]);
                
            }
        }
        strip->show();
        yield();
        delay(_speed);
    }
}