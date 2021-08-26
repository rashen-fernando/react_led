#include "FastLED.h"
CRGB leds[60];
void setup() { FastLED.addLeds<NEOPIXEL, 2>(leds, 60); }
void loop() { 
  
  leds[1].setRGB( 100,0,0);
  FastLED.show();
  delay(10);
}



//just on off all the light at once for a pulse
void mode1()
{
   for(int k=0;k<count;k++)
  {
  // Turn the LED on, then pause
  leds[k].setRGB(100,0,0);
  FastLED.show();
  }
  delay(50);
   for(int k=0;k<count;k++)
  {
  // Turn the LED on, then pause
  leds[k].setRGB(0,0,0);
  FastLED.show();
  }

}




//start to light on from previous last lit led
void mode2()
{
  if(count-pre_count > 0)
  {
    for(int k=pre_count;k<count;k++)
      {// Turn the LED on, then pause
        leds[k].setRGB(100,0,0);
        FastLED.show();
      }
  }
  else
  {
    for(int k=pre_count;k>count;k--)
      {
        leds[k].setRGB(0,0,0);
        FastLED.show();
      }
  }
}


/*fastled
0.Setting RGB Colours :  1.leds[i].r = 255; 
                           leds[i].g = 68; 
                           leds[i].b = 221;

                         2.leds[i] = 0xFF44DD; //hex colour code

                         3.leds[i] = CRGB::HotPink; //html way

                         4.leds[i].setRGB( 255, 68, 221);

                         5.leds[i] = leds[j];

                         6.leds[i] = CHSV( 224, 187, 255); //hue,saturation,value

                              
1.adding two colours  :   leds[i] += newTint;

2.brightness          :   val = dim8_raw(val);
                          val = dim8_video(val);
                          val = brighten8_raw(val);
                          val = brighten8_video(val);

3.random numbers      :   random8()       == random from 0..255
                          random8( n)     == random from 0..(N-1)
                          random8( n, m)  == random from N..(M-1)

4.trig functions      :   sin16(x);//degrees
                          cos16(x);
                          sin8(x);
                          cos8(x);

5.easing in out       :   ease8InOutCubic(x) == 3(x^i) - 2(x^3)   //get rid off 
                          ease8InOutApprox(x) == 
                          faster, rougher, approximation of cubic easing

6.adding a little red :   leds[i] += CRGB( 20, 0, 0)

7.Add a constant 
  amount brightness
  to all(RGB)chnnls   :   leds[i].addToRGB(20);
  .

8.brghtness increase  :   leds[i]++;
                          leds[i].addToRGB(20);

9.brightness down     :   leds[i].subtractFromRGB(20);

10.dimming            :   leds[i].fadeLightBy( 64 );   // Dim a color by 25% (64/256ths)
                          leds[i] %= 192;              // Reduce color to 75% (192/256ths) of its previous value
                          leds[i].fadeToBlackBy( 64 ); //eventually fading to full black ,Dim a color by 25% (64/256ths)  
                          leds[i].nscale8( 192);
                          
11.brighten           :   leds[i].maximizeBrightness(); // Adjust brightness to maximum possible while keeping the same hue.
                          leds[i] /= 2;                 //Divide each channel by a single value
                          leds[i] *= 2;                 // Multiply each channel by a single value
                          
12.Constraining Clrs  :   leds[i] |= CRGB( 32, 48, 64);  leds[i] |= 96; //minimum
   Within Limits          leds[i] &= CRGB( 192, 128, 192),  leds[i] &= 160;//maximum

13.CRGBSet            :   leds(i,i+1) = CRGB::Red  // 2 led units are considered one unot

14.
*/
   
                                                    
