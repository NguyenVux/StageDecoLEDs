#include <Adafruit_NeoPixel.h>
 
//#define PIN 5
#define PIN 5
#define maxLED 50
Adafruit_NeoPixel strip = Adafruit_NeoPixel(maxLED, PIN, NEO_RGB + NEO_KHZ800);

void Trail(unsigned char* colors);
void Snake(unsigned char* r, unsigned char* g,unsigned char* b);
void litAll(unsigned char* r, unsigned char* g,unsigned char* b);
void Alternative(unsigned char* r, unsigned char* g,unsigned char* b);
void setColor(unsigned char* index,unsigned char* colors);
void ClearBuffer()
{
  while(Serial.available() >0)
  {
    Serial.read();
  }
}


void setup(){  
    strip.begin();  
    strip.clear();
    Serial.begin(115200);
    //strip.setPixelColor(1,253,184,19);
    
    strip.show();
}
void loop(){
  static unsigned char colors[3] = {253,184,19};
  Serial.println("123");
  Trail(colors);
}

void Trail(unsigned char* colors)
{
    strip.clear();
    for(unsigned char i  = 0; i < maxLED; ++i)
    {
      setColor(&i,colors);
      strip.show();
      delay(30);
    }
}

void Snake(unsigned char* r, unsigned char* g,unsigned char* b)
{
    for(char i  = 0; i < maxLED; ++i)
    {
      strip.clear();
      strip.setPixelColor(i,*b,*r,*g);    
      strip.show();
      delay(30);
    }
}
void Alternative(unsigned char* r, unsigned char* g,unsigned char* b)
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
            strip.setPixelColor(k,*b,*r,*g);    
          }
        }
        else
        {
          if(!(k%2))
          {
            strip.setPixelColor(k,*b,*r,*g);    
          }
        }
      }
      strip.show();
      delay(500);
    }
}

void litAll(unsigned char* r, unsigned char* g,unsigned char* b)
{
  for(char i  = 0; i < maxLED; ++i)
    {
      strip.setPixelColor(i,*b,*r,*g);    
    }
}

void setColor(unsigned char* index,unsigned char* colors)
{
  unsigned char byteCount = 0;
   while(Serial.available() >0)
  {
    if(Serial.available()>3)
    {
      ClearBuffer();
      Serial.println(true);
      break;
    }
    colors[byteCount++] = Serial.read();
    Serial.println(colors[byteCount-1],HEX);
    if(byteCount == 3)
    {
      Serial.println("break");
      break;
    }
  }
  strip.setPixelColor(*index,colors[2],colors[0],colors[1]);
}
