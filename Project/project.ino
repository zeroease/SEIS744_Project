//ANTONIO DITOMMASO PROJECT FOR SEIS 744-01
//CODE PULLED FROM https://particle.hackster.io/Richa1/kid-tracker-1b58c9
// This #include statement was automatically added by the Particle IDE.
#include "application.h"
#include "neopixel/neopixel.h"
#include "TinyGPS/TinyGPS.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D7
#define PIXEL_COUNT 20
#define PIXEL_TYPE WS2812B
#define HELP_BUTTON D5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

TinyGPS gps;
char szInfo[64];
int show = 1;
int R;
int G;
int B;
int FadeR;
int FadeG;
int FadeB;
int wait = 14000;


void setup()
{
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    Spark.function("led",ledToggle);
    Serial1.begin(9600);
    Particle.publish("TGest");
    pinMode(HELP_BUTTON, INPUT_PULLUP);
    
}

void loop(){

      switch (show) {
    case 1:    // your hand is nowhere near the sensor
      Sparkle(50);
      break;
    case 2:    // your hand is close to the sensor
      colorWipe(strip.Color(R, G, B), wait);
      colorWipe(strip.Color(0, 0, 0), wait);
      break;
    case 3:    // your hand is close to the sensor
      colorWipe(strip.Color(R, G, B), wait);
      colorWipe(strip.Color(0, 0, 0), wait);
      break;
    case 4:    // your hand is close to the sensor
      colorWipe(strip.Color(R, G, B), wait);
      colorWipe(strip.Color(0, 0, 0), wait);
      bool isValidGPS = false;
    
    for (unsigned long start = millis(); millis() - start < 1000;){
        // Check GPS data is available
        while (Serial1.available()){
            char c = Serial1.read();
            
            // parse GPS data
            if (gps.encode(c))
                isValidGPS = true;
        }
    }

    // If we have a valid GPS location then publish it
    if (isValidGPS){
        float lat, lon;
        unsigned long age;
    
        gps.f_get_position(&lat, &lon, &age);

        sprintf(szInfo, "%.6f,%.6f", (lat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lat), (lon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lon));

    }
    
    Particle.publish("gpsloc", szInfo);
      break;
  }
  delay(1);        // delay in between reads for stability

}
int ledToggle(String command) {
    if (command=="Play") {
        colorAll(strip.Color(0, 0, 0), 0);
        R = 0;
        G = 200;
        B = 255;
        wait = 50;
        show = 1;
        return 1;
    } else if (command=="Home"){
        R = 255;
        G = 100;
        B = 0;
        wait = 75;
        show = 2;
        return 2;
        
    } else if (command=="Walk"){
        R = 0;
        G = 255;
        B = 0;
        wait = 50;
        show = 3;
        return 3;
} else if (command=="Help"){
        R = 255;
        G = 0;
        B = 0;
        wait = 50;
        show = 4;
        return 4;
    }
    
  delay(1);        // delay in between reads for stability
}
  
  void CheckSwitch()
  {
    if (digitalRead(HELP_BUTTON) == LOW) {
        R = 255;
        G = 0;
        B = 0;
        wait = 50;
        show = 4;
  }
  }
  
// Set all pixels in the strip to a solid color, then wait (ms)
void colorAll(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    CheckSwitch();
  }
  strip.show();
  delay(wait);
}

// Fill the dots one after the other with a color, wait (ms) after each one
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    CheckSwitch();
    delay(wait);
  }
}

void Sparkle(int t){
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        if (random(3000) < t) {
            FadeR = R;
            FadeG = G;
            FadeB = B;
        } else {
            FadeR = (strip.getPixelColor(i) >> 16) & 0xFF;
            FadeG = (strip.getPixelColor(i) >> 8) & 0xFF;
            FadeB = strip.getPixelColor(i) & 0xFF;
            delay(5);
          FadeR = FadeR-(R/50);
          if(FadeR < 5) {
            FadeR = 0;
          }
          FadeG = FadeG-(G/50);
          if(FadeG < 5) {
            FadeG = 0;
          }
          FadeB = FadeB-(B/50);
          if(FadeB < 5) {
            FadeB = 0;
          }
        }
        strip.setPixelColor(i, FadeR, FadeG, FadeB);
        CheckSwitch();
      }
    strip.show();
}
