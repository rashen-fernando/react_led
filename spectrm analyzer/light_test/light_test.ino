#include "FastLED.h"
#define NUM_LEDS 60


#define DATA_PIN 2
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() 
{ 
   FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() { 
  for(int i=0;i<60;i++)
  {
  // Turn the LED on, then pause
  leds[i] = CRGB::White;
  FastLED.show();
  delay(50);
  leds[i] = CRGB::Yellow;
  FastLED.show();
  }
  // Now turn the LED off, then pause
  

}
