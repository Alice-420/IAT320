#include <Adafruit_CircuitPlayground.h>
#include <FastLED.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, 6, NEO_GRB + NEO_KHZ800);
Adafruit_LSM303DLH_Mag_Unified accel = Adafruit_LSM303DLH_Mag_Unified(54321);

uint8_t brightness = 50;  // Set brightness level

int STEPS = 3;  //makes the rainbow colors more or less spread out
int NUM_MODES = 2;  // change this number if you add or subtract modes
int CYCLETIME = 10;  // number of seconds on each mode, for mode cycling
 
CRGB leds[NUM_LEDS];      // set up an LED array

#define MOVE_THRESHOLD 80

void setup() 
{
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ); // Use this line if using neopixels
  currentBlending = LINEARBLEND;
  set_max_power_in_volts_and_milliamps(3, 3000);    
  if (!accel.begin())
  {
    while (1);
  }
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);
  Serial.print("Accel X: "); Serial.print(event.acceleration.x); Serial.print(" ");
  Serial.print("Y: "); Serial.print(event.acceleration.y);       Serial.print(" ");
  Serial.print("Z: "); Serial.print(event.acceleration.z);     Serial.print(" ");

  double storedVector = event.acceleration.x*event.acceleration.x;
  storedVector += event.acceleration.y*event.acceleration.y;
  storedVector += event.acceleration.z*event.acceleration.z;
  storedVector = sqrt(storedVector);
  Serial.print("Len: "); Serial.println(storedVector);
  
  // wait a bit
  delay(30);
  
  // get new data!
  accel.getEvent(&event);
  double newVector = event.acceleration.x*event.acceleration.x;
  newVector += event.acceleration.y*event.acceleration.y;
  newVector += event.acceleration.z*event.acceleration.z;
  newVector = sqrt(newVector);
  Serial.print("New Len: "); Serial.println(newVector);
  
  // are we moving 
  if (abs(newVector - storedVector) > MOVE_THRESHOLD) {
    Serial.println("Wing moves");
   
  }

      
    // turn on green and blue light
    switch (ledMode) {        
       case 0: currentPalette = OceanColors_p; rainbow(); break;                    
       case 1: currentPalette = ForestColors_p; rainbow(); break;  
       case 99: clearpixels(); break;         
    }
}

void rainbow(){
  
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
 
  FillLEDsFromPaletteColors( startIndex);
 
  FastLED.show();
  FastLED.delay(20); 
  }
 
//this bit is in every palette mode, needs to be in there just once
void FillLEDsFromPaletteColors( uint8_t colorIndex){ 
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += STEPS;
  }
}

int cycleMode=0;
void dangerLight(){
   switch (cycleMode) {
                         
       case 0: currentPalette = LavaColors_p; rainbow(); break;   
       case 5: cycleMode=0; break;
  }
}
