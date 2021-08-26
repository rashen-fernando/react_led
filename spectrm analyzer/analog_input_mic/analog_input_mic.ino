//freq range - 150 Hz to 4300 Hz

#include "arduinoFFT.h"
#include "FastLED.h"
arduinoFFT FFT = arduinoFFT();

#define CHANNEL 4
#define DIGITAL 5

#define NUM_LEDS 60

#define DATA_PIN 2
#define CLOCK_PIN 13

const uint16_t samples = 128; //This value MUST ALWAYS be a power of 2
const double samplingFrequency = 9000; //Hz, must be less than 10000 due to ADC

unsigned int sampling_period_us;
unsigned long microseconds;

// Define the array of leds
CRGB leds[NUM_LEDS];

/*
These are the input and output vectors
Input vectors receive computed results from FFT
*/
double vReal[samples];
double vImag[samples];
double m;
#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

double ave,val=0;
int count=0;
int pre_count = 0;
int red = 100;
int green,blue =0 ;
float x;

void setup(){
  Serial.begin(256000);
  pinMode(CHANNEL, INPUT);
  pinMode(DIGITAL,INPUT);
  sampling_period_us = round(1000000*(1.0/samplingFrequency));
 FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
 for(int i=0;i<50000;i++)
 {
    ave = ave+ analogRead(CHANNEL);
 }
 
 ave = ave/50000; 
}







void loop()
{

//taking audio buffer
  microseconds = micros();
  for(int i=0; i<samples; i++)
    {
    if(digitalRead(DIGITAL)==1)
    { 
      vReal[i] = analogRead(CHANNEL)-ave;
      vImag[i] = 0;
      
    }
   else
    {
      vReal[i] = 0;
      vImag[i] = 0;
    }
      
      while(micros() - microseconds < sampling_period_us){
        //empty loop
      }
      microseconds += sampling_period_us;
  }
 
//fft
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samples); 
  //PrintVector(vReal, (samples >> 1), SCL_FREQUENCY);
  x = FFT.MajorPeak(vReal, samples, samplingFrequency);

   for(int i=0;i<sizeof(vReal)/sizeof(double);i++)
   {
      m=max(m,vReal[i]);
   }

   count = round(map(m,0,30000,0,50));

   mode5();
   
   mode2();

//    Serial.print(red);
//    Serial.print("  ");
    Serial.println(x);
 pre_count=count; 
  m=0;
    
}










void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = 0; i < bufferSize; i++)
  {
    double abscissa;
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
  break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / samplingFrequency);
  break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * samplingFrequency) / samples);
  break;
    }
    Serial.print(abscissa, 6);
    if(scaleType==SCL_FREQUENCY)
      Serial.print("Hz");
    Serial.print(" ");
    Serial.println(vData[i], 4);
  }
  Serial.println();
}










//just on off all the light at once for a pulse
void mode1()
{
   for(int k=0;k<count;k++)
  {
  // Turn the LED on, then pause
  leds[k].setRGB(red,green,blue);
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
    for(int k=pre_count;k<=count;k++)
      {// Turn the LED on, then pause
        leds[k].setRGB(red,green,blue);
        FastLED.show();
      }
  }
  else
  {
    for(int k=pre_count;k>=count;k--)
      {
        leds[k].setRGB(0,0,0);
        FastLED.show();
      }
  }

}


void mode3()
{
  float w=0.2168;
  if(100<x&&x<3000)
  {
  red = sin8(w*x);
  green = sin8(w*x-23.421);
  blue = sin8(w*x-37.2616);
  }
  else{red=100;green=0;blue=0;}
}



void mode4()
{
  double val = pow(2,40)*x/pow(10,12);
  double p_red = 100000*exp(-0.5* pow((x - 200)/400 , 2) )/400;
  double p_green = 100000*exp(-0.5* pow((x - 700)/400 , 2) )/400;
  double p_blue = 100000*exp(-0.5* pow((x - 1200)/400 , 2) )/400;
  red = round(p_red);
  green = round(p_green);
  blue = round(p_blue);
  Serial.print(p_red);
  Serial.print("    ");
  Serial.print(p_green);
  Serial.print("    ");
  Serial.println(p_blue);
  //Serial.println(val);
}



void mode5()
{
  if(x<300)
  {
    red = round(map(x,0,300,0,255));
    green = 0;
    blue=255-red;
  }

  else if(x>300 && x<500)
  {
  
    green = round(map(x,300,500,0,255));
      red = 255 -green;
    blue=0;
  }
  else if(x>500 && x<2000)
  {
    red = 0;
    blue= round(map(x,500,2000,0,255));
    green = 255-blue;
    
  }
  else if(x>2000 && x<3000)
  {
    red =  map(x,800,3000,0,255);
    green =0;
    blue=255-red;
  }
  else
  {
    mode6;
  }
}


void mode6()
{
  red =  round(random(100,255));
    green =round(random(100,255));
    blue=round(random(100,255));
}
