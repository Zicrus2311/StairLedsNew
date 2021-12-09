#include "games.h"

#include <FastLED.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <EEPROM.h>

#include "..\colorUtils\hsvRgb.h"
#include "idle.h"
#include "ledRun.h"

bool* games::startDown;
bool* games::startPrev;
bool* games::stopDown;
bool* games::stopPrev;

CRGB* games::leds;
int games::numLeds;

LiquidCrystal* games::lcd;

games::Modes games::curMode;
unsigned long games::modeBeginTime;

games::LcdModes games::curLcdMode;

void games::fillStrip(const CRGB& color) {
    for (int i = 0; i < numLeds; i++) {
        leds[i] = color;
    }
}

void games::initialize(bool& startDown, bool& startPrev, bool& stopDown, bool& stopPrev, CRGB* leds, const int& numLeds, LiquidCrystal& lcd) {
    games::startDown = &startDown;
    games::startPrev = &startPrev;
    games::stopDown = &stopDown;
    games::stopPrev = &stopPrev;

    games::leds = leds;
    games::numLeds = numLeds;

    games::lcd = &lcd;
}

void games::switchMode(const Modes& newMode) {
    curMode = newMode;
    modeBeginTime = millis();
}

void games::switchLcdMode(const LcdModes& newLcdMode) {
    curLcdMode = newLcdMode;
    
    games::lcd->clear();
    
    unsigned long time;
    switch(newLcdMode) {
    case LcdModes::Time:
        games::lcd->setCursor(0, 0);
        games::lcd->print("Time:");
        
        EEPROM.get<unsigned long>(0, time);

        games::lcd->setCursor(0, 1);
        games::lcd->print(time / 1000);
        games::lcd->print(",");
        games::lcd->print(time % 1000);
        games::lcd->print(" s");
        break;
    case LcdModes::Speed:
        games::lcd->setCursor(0, 0);
        games::lcd->print("Time:");
        
        EEPROM.get<unsigned long>(0, time);
        float speed = 9 / (time / 1000.0);

        games::lcd->setCursor(0, 1);
        games::lcd->print(speed);
        games::lcd->print(" m/s");
        break;
    }
}

void games::cycleLcdModes() {
    switch(games::curLcdMode) {
    case games::LcdModes::Time:
        games::switchLcdMode(games::LcdModes::Speed);
        break;
    case games::LcdModes::Speed:
        games::switchLcdMode(games::LcdModes::Time);
        break;
    }
}

void games::gameLoop() {
    switch (curMode) {
        case Modes::Idle:
            idle::idleLoop();
            break;
        case Modes::LedRun:
            ledRun::gameLoop();
            break;
    }
}