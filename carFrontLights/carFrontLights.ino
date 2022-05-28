#include <FastLED.h>

/* --=== Constant values: ===-- */
#define LED_PIN_R 7
#define LED_PIN_L 8
#define LED_OFFSET 0
#define NUM_LEDS 26

uint8_t firstLed = 0 + LED_OFFSET;
uint8_t middleLed = (NUM_LEDS/2) + LED_OFFSET;
uint8_t lastLed = NUM_LEDS + LED_OFFSET - 1;
uint8_t noLed = NUM_LEDS + LED_OFFSET;  //Position after the last led.

CRGB leds_r[NUM_LEDS];
CRGB leds_l[NUM_LEDS];
long randNum;

void setup() {

  FastLED.addLeds<WS2812, LED_PIN_R, GRB>(leds_r, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_L, GRB>(leds_l, NUM_LEDS);
}

void loop() {
  turnOn(leds_r, leds_l);
  delay(1000);
  turnOff(leds_r, leds_l);
  //whiteDimming(leds);
  delay(500);
  //turnOff(leds);
  //strobeFlashes(leds);
}



/* --=== Lighting Patterns & Effects ===-- */

/* Turns off all the LEDs. Range in this case is longer and is not using first and last LED definitions.
 * This is because we have a PCB with 86 LEDs, but also we have a LED and a microcontroller (uC) in the
 * carrier. This way we assure all the LEDs are totally off. */
void turnOff(CRGB leds_r[], CRGB leds_l[]){
  for(uint8_t led=firstLed; led<lastLed+1; led++){
        leds_r[led] = CRGB(0, 0, 0);
		leds_l[led] = CRGB(0, 0, 0);
        FastLED.show();
        delay(1);
  }
}

/* Turns on all the LEDs of the kidney PCB. */
void turnOn(CRGB leds_r[], CRGB leds_l[]){
  uint8_t led;
  for(led=firstLed; led<lastLed+1; led++){
    leds_r[led] = CRGB (100, 100, 100);
	leds_l[led] = CRGB (100, 100, 100);
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
