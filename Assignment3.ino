#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, 6, NEO_GRB + NEO_KHZ800);
Adafruit_LSM303DLH_Mag_Unified accel = Adafruit_LSM303DLH_Mag_Unified(54321);

// Here is where you can put in your favorite colors that will appear!
// just add new {nnn, nnn, nnn}, lines. They will be picked out randomly
//                                  R   G   B
uint8_t myFavoriteColors[][3] = {{255,   0, 255},   // purple
                                 {255,   135,   130},   // vioelt 
                                 {200, 200, 200},   // white
                               };

#define FAVCOLORS sizeof(myFavoriteColors) / 3

#define MOVE_THRESHOLD 80

void setup() 
{
  Serial.begin(9600);
  
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
    Serial.println("Twinkle!");
    flashRandom(1, 1);  // first number is 'wait' delay, shorter num == shorter twinkle
    flashRandom(1, 3);  // second number is how many neopixels to simultaneously light up
    flashRandom(1, 2);
  }
}

void flashRandom(int wait, uint8_t howmany) {

  for(uint16_t i=0; i<howmany; i++) {
    // pick a random favorite color!
    int c = random(FAVCOLORS);
    int red = myFavoriteColors[c][0];
    int green = myFavoriteColors[c][1];
    int blue = myFavoriteColors[c][2]; 

    // get a random pixel from the list
    int j = random(strip.numPixels());
    //Serial.print("Lighting up "); Serial.println(j); 
    
    // now we will 'fade' it in 5 steps
    for (int x=0; x < 5; x++) {
      int r = red * (x+1); r /= 5;
      int g = green * (x+1); g /= 5;
      int b = blue * (x+1); b /= 5;
      
      strip.setPixelColor(j, strip.Color(r, g, b));
      strip.show();
      delay(wait);
    }

    for (int x=5; x >= 0; x--) {
      int r = red * x; r /= 5;
      int g = green * x; g /= 5;
      int b = blue * x; b /= 5;
      
      strip.setPixelColor(j, strip.Color(r, g, b));
      strip.show();
      delay(wait);
    }
  }
  // LEDs will be off when done (they are faded to 0)
}
