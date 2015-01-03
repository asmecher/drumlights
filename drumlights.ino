/**
 * Drum lights: Trigger-driven drum illumination
 * Alec Smecher, 2014
 * http://www.cassettepunk.com
 */

#include <Adafruit_NeoPixel.h>

/**
 * Pin configuration
 */
#define STRIP_PIN 0 // The digital pin # for the neopixel output
#define PIEZO_DIG_PIN 2 // The digital pin # for the piezo input
#define PIEZO_ANALOG_PIN 1 // The analog pin # for the piezo input

/**
 * Neopixel strip lengths for each unit
 */
#define BD_LENGTH 107
#define SNARE_LENGTH 60
#define CYM_LENGTH 48
#define HH_LENGTH 34

uint32_t Wheel(byte WheelPos, float intensity = 1);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(HH_LENGTH, STRIP_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(PIEZO_DIG_PIN, INPUT);
  strip.begin();
}

unsigned char n=0; // Counter for colour wheel effect

void loop() {
  // Perform the pixel chase
  for (int i=strip.numPixels(); i>0; i--) {
    strip.setPixelColor(i, strip.getPixelColor(i-1));
  }

  // Set the first pixel using the current piezo value
  strip.setPixelColor(0, Wheel(n++, analogRead(PIEZO_ANALOG_PIN)/1024.0));

  // Update the strip
  strip.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// This function adapted from Adafruit's demo code to add intensity.
uint32_t Wheel(byte WheelPos, float intensity) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color((255 - WheelPos * 3) * intensity, 0, WheelPos * 3 * intensity);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3 * intensity, (255 - WheelPos * 3) * intensity);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3 * intensity, (255 - WheelPos * 3) * intensity, 0);
  }
}
