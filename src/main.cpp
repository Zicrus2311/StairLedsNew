#include <Arduino.h>
#include <FastLED.h>

#include "colorUtils/hsvRgb.h"
#include "games/games.h"

#define STOP_PIN 5
#define EASY_PIN 4
#define MEDIUM_PIN 3
#define HARD_PIN 2

bool stopDown;
bool easyDown;
bool mediumDown;
bool hardDown;

#define LED_PIN 10
#define NUM_LEDS 258

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(STOP_PIN, INPUT_PULLUP);
  pinMode(EASY_PIN, INPUT_PULLUP);
  pinMode(MEDIUM_PIN, INPUT_PULLUP);
  pinMode(HARD_PIN, INPUT_PULLUP);

  games::initialize(leds, NUM_LEDS, stopDown, easyDown, mediumDown, hardDown);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  stopDown = !digitalRead(STOP_PIN);
  easyDown = !digitalRead(EASY_PIN);
  mediumDown = !digitalRead(MEDIUM_PIN);
  hardDown = !digitalRead(HARD_PIN);

  games::gameLoop();
  
  FastLED.show();
}