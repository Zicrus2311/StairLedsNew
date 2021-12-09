#include "ledRun.h"

#include <FastLED.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <EEPROM.h>

#include "games.h"

bool ledRun::started = false;
bool ledRun::stopped = false;
unsigned long ledRun::startTime;
unsigned long ledRun::stopTime;
unsigned long ledRun::time;
unsigned long ledRun::lastTime;
bool ledRun::won = false;

void ledRun::gameLoop() {
    // Start
    if(!*games::startDown && !started) {
        started = true;
        startTime = millis();
        EEPROM.get(0, lastTime);
        games::switchLcdMode(games::LcdModes::Time);
        games::lcd->clear();
    }
    if(!started) {
        games::fillStrip(CRGB(0, 255, 0));
        return;
    }

    // Stop
    if(stopped && *games::stopDown && !*games::stopPrev) {
        games::cycleLcdModes();
        stopTime = millis();
    }
    if((*games::stopDown || millis() - startTime > 20000) && !stopped) {
        stopped = true;
        stopTime = millis();

        if(millis() - startTime <= 20000 && millis() - startTime >= 1000) {
            EEPROM.put<unsigned long>(0, millis() - startTime);
        }
        else {
            games::switchLcdMode(games::LcdModes::Time);
        }
    }
    if(stopped) {
        if(millis() - stopTime > 2000) {
            started = false;
            stopped = false;
            won = false;
            games::switchMode(games::Modes::Idle);
        }

        int timePerLed = lastTime/games::numLeds;
        int ledCount = time/timePerLed;
        CRGB litColor = won ? CRGB(0, 255, 0) : CRGB(255, 0, 0);
        litColor = millis() % 250 > 125 ? litColor : CRGB(0, 0, 0);
        for (int i = 0; i < games::numLeds; i++) {
            bool lit = i >= games::numLeds - ledCount;
            games::leds[i] = lit ? litColor : CRGB(0, 0, 0);
        }
        return;
    }

    // Game
    int timePerLed = lastTime/games::numLeds;
    time = millis() - startTime;
    int ledCount = time/timePerLed;
    won = ledCount < games::numLeds;
    CRGB litColor = won ? CRGB(0, 255, 0) : CRGB(255, 0, 0);
    for (int i = 0; i < games::numLeds; i++)
    {
        bool lit = i >= games::numLeds - ledCount;
        games::leds[i] = lit ? litColor : CRGB(0, 0, 0);
    }

    // Time
    games::lcd->setCursor(0, 0);
    games::lcd->print("Time:");

    games::lcd->setCursor(0, 1);
    games::lcd->print(time / 1000);
    games::lcd->print(",");
    games::lcd->print(time % 1000);
    games::lcd->print(" s");
}