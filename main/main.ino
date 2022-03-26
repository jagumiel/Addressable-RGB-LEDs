#include <FastLED.h>

/* --=== Constant values: ===-- */
#define LED_PIN 7
#define LED_OFFSET 0
#define NUM_LEDS 30

uint8_t firstLed = 0 + LED_OFFSET;
uint8_t middleLed = (NUM_LEDS/2) + LED_OFFSET;
uint8_t lastLed = NUM_LEDS + LED_OFFSET - 1;
uint8_t noLed = NUM_LEDS + LED_OFFSET;  //Position after the last led.

CRGB leds[NUM_LEDS];
long randNum;

void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
}

void loop() {
  for(int i=0; i<500; i++){
    strobeClassic(leds);
  }
  turnOn(leds);
  delay(1000);
  turnOff(leds);
  whiteDimming(leds);
  delay(500);
  turnOff(leds);
  strobeFlashes(leds);
  // randNum = random(0,NUM_LEDS);
  // leds[randNum] = CRGB(255, 255, 255);
  // FastLED.show();
  // delay(20);
  // leds[randNum] = CRGB(0, 0, 0);
  // FastLED.show();
  // delay(20);
}



/* --=== Lighting Patterns & Effects ===-- */

/* Turns off all the LEDs. Range in this case is longer and is not using first and last LED definitions.
 * This is because we have a PCB with 86 LEDs, but also we have a LED and a microcontroller (uC) in the
 * carrier. This way we assure all the LEDs are totally off. */
void turnOff(CRGB leds[]){
  for(uint8_t led=firstLed; led<lastLed+1; led++){
        leds[led] = CRGB(0, 0, 0);
        FastLED.show();
        delay(1);
  }
}

/* Turns on all the LEDs of the kidney PCB. */
void turnOn(CRGB leds[]){
  uint8_t led;
  for(led=firstLed; led<lastLed+1; led++){
    leds[led] = CRGB (100, 100, 100);
  }
}

void strobeFlashes(CRGB leds[]){
    long randNum=0;
    for(int reps=0; reps<1000; reps++){
        randNum = random(0, NUM_LEDS);
        leds[randNum] = CRGB(255, 255, 255);
        FastLED.show();
        delay(20);
        leds[randNum] = CRGB(0, 0, 0);
        FastLED.show();
        delay(20);
    }
}

void strobeClassic(CRGB leds[]){
    uint8_t led;
    for(led=firstLed; led<lastLed+1; led++){
      leds[led] = CRGB(255, 255, 255);
      FastLED.show();
    }
    delay(20);
    for(led=firstLed; led<lastLed+1; led++){
      leds[led] = CRGB(0, 0, 0);
      FastLED.show();
    }
    delay(20);
}

/* White dimming effect. It goes from off to maximum brightness. */
void whiteDimming(CRGB leds[]){
  uint8_t brightness, led;
  for(brightness=0; brightness<255; brightness++){ // brightness [0-255]
    for(led=firstLed; led<lastLed+1; led++){
      leds[led] = CRGB(brightness, brightness, brightness);
      FastLED.show();
    }
    delay(10);
  }
}
