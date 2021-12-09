#include <Arduino.h>
#include <FastLED.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#include "colorUtils/hsvRgb.h"
#include "games/games.h"

// Buttons
#define START_PIN 9
#define STOP_PIN 8

bool startDown;
bool startPrev;
bool stopDown;
bool stopPrev;

// LED strip
#define LED_PIN 10
#define NUM_LEDS 258

CRGB leds[NUM_LEDS];

// LCD display
#define LCD_RS 12
#define LCD_ENABLE 11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  pinMode(START_PIN, INPUT_PULLUP);
  pinMode(STOP_PIN, INPUT_PULLUP);

  games::initialize(startDown, startPrev, stopDown, stopPrev, leds, NUM_LEDS, lcd);
  games::switchMode(games::Modes::Idle);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 250);
  FastLED.clear();
  FastLED.show();

  lcd.begin(16, 2);
  games::switchLcdMode(games::LcdModes::Time);
}

void loop() {
  startDown = !digitalRead(START_PIN);
  stopDown = !digitalRead(STOP_PIN);

  games::gameLoop();
  
  FastLED.show();

  startPrev = startDown;
  stopPrev = stopDown;
}