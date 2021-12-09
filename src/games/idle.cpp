#include "idle.h"

#include <Arduino.h>
#include <FastLED.h>

#include "..\colorUtils\hsvRgb.h"
#include "games.h"

void idle::rainbow() {
    for (int i = 0; i < games::numLeds; i++) {
        games::leds[i] = hsvRgb::q_hue2rgb(i + millis() / 20);
    }
}

void idle::idleLoop() {
    if(*games::stopDown && !*games::stopPrev) games::cycleLcdModes();

    if(*games::startDown) games::switchMode(games::Modes::LedRun);
    
    rainbow();
}