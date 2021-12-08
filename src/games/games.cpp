#include "games.h"

#include "FastLED.h"

#include "..\colorUtils\hsvRgb.h"
#include "whackAMole.h"

bool* games::stopDown;
bool* games::easyDown;
bool* games::mediumDown;
bool* games::hardDown;

CRGB* games::leds;
int games::numLeds;

games::Modes games::curMode;
unsigned long games::modeBeginTime;

void games::fillStrip(const CRGB& color) {
    for (int i = 0; i < numLeds; i++) {
        leds[i] = color;
    }
}

void games::rainbow() {
    if(*stopDown) fillStrip(CRGB(255, 255, 255));
    else if(*easyDown) fillStrip(CRGB(0, 255, 0));
    else if(*mediumDown) fillStrip(CRGB(255, 255, 0));
    else if(*hardDown) fillStrip(CRGB(255, 0, 0));
    else {
        for (int i = 0; i < numLeds; i++) {
            leds[i] = hsvRgb::q_hue2rgb(i + (millis() - modeBeginTime) / 50);
        }
    }
}

void games::initialize(CRGB* leds, const int& numLeds, bool& stopDown, bool& easyDown, bool& mediumDown, bool& hardDown) {
    games::stopDown = &stopDown;
    games::easyDown = &easyDown;
    games::mediumDown = &mediumDown;
    games::hardDown = &hardDown;

    games::leds = leds;
    games::numLeds = numLeds;
}

void games::switchMode(const Modes& newMode) {
    curMode = newMode;
    modeBeginTime = millis();
}

void games::gameLoop() {
    switch (curMode) {
        case Modes::Rainbow:
            rainbow();
            break;
        case Modes::WhackAMole:
            whackAMole::gameLoop();
            break;
    }
}