#include <Adafruit_NeoPixel.h>
 
#define PIN 6
#define maxLED 20
Adafruit_NeoPixel strip = Adafruit_NeoPixel(maxLED, PIN, NEO_RGB + NEO_KHZ800);

void Trail(const char& r, const char& g,const char& b);
void Snake(const char& r, const char& g,const char& b);
void litAll(const char& r, const char& g,const char& b);
void Alternative(const char& r, const char& g,const char& b);
void setup(){  
    strip.begin();  
    strip.clear();
    Serial.begin(115200);
    strip.show();
}
void loop(){
  static char choice = 0;
  unsigned char byteCount = 0;
  static unsigned char colors[3] = {255,0,0};
  while(Serial.available())
  {
    colors[byteCount++] = Serial.read();
    if(byteCount == 3)
    {
      break;
    }
  }
  Serial.print("Add: ");
  Serial.print((int)&colors[0],HEX);
  Trail(colors[0],colors[1],colors[2]);
}

void Trail(const char& r, const char& g,const char& b)
{
  Serial.print("Add-Red: ");
  Serial.print(r,HEX);
    strip.clear();
    for(char i  = 0; i < maxLED; ++i)
    {
      strip.setPixelColor(i,b,r,g);    
      strip.show();
      delay(30);
    }
}

void Snake(const char& r, const char& g,const char& b)
{
    for(char i  = 0; i < maxLED; ++i)
    {
      strip.clear();
      strip.setPixelColor(i,b,r,g);    
      strip.show();
      delay(30);
    }
}
void Alternative(const char& r, const char& g,const char& b)
{
    for(char i  = 0; i < 5; ++i)
    {
      strip.clear();
      for(char k = 0; k < maxLED;++k)
      {
        if(i%2)
        {
          if(k%2)
          {
            strip.setPixelColor(k,b,r,g);    
          }
        }
        else
        {
          if(!(k%2))
          {
            strip.setPixelColor(k,b,r,g);    
          }
        }
      }
      strip.show();
      delay(500);
    }
}

void litAll(const char& r, const char& g,const char& b)
{
  for(char i  = 0; i < maxLED; ++i)
    {
      strip.setPixelColor(i,b,r,g);    
    }
}
