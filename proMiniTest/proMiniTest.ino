#include <Adafruit_NeoPixel.h>
 
#define PIN 6
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_RGB + NEO_KHZ800);
 
void setup(){  
 
    strip.begin();  
    strip.clear();

    Serial.begin(9600);
}
 
void loop(){
    strip.clear();
    for(char i  = 0; i < 50; ++i)
    {
      strip.setPixelColor(i,i*5,i*2,255-i*4);    
      strip.show();
      delay(70);
    }
 
}
