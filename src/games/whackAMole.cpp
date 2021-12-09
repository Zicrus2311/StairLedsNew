#include "whackAMole.h"

#include "FastLED.h"

#include "games.h"

bool whackAMole::pressedLastFrame = false;
int whackAMole::curLed = 0;
int whackAMole::lastLed = 0;
int whackAMole::lastPressTime = 0;
bool whackAMole::travelling = false;

void whackAMole::gameLoop() {
    if((*games::stopDown || *games::hardDown) && !pressedLastFrame && !travelling) {
        lastPressTime = millis();
        lastLed = curLed;
        curLed = random(0, games::numLeds);
        travelling = true;
    }
    pressedLastFrame = (*games::stopDown || *games::hardDown);

    if (travelling) {
        int dir = curLed > lastLed ? 1 : -1;
        long travelTime = millis() - lastPressTime;
        int tempLed = lastLed + travelTime * dir * games::numLeds / 1000;
        tempLed = constrain(tempLed, 0, games::numLeds - 1);

        if(abs(tempLed - lastLed) >= abs(curLed - lastLed)) {
            travelling = false;
        }
        else {
            games::fillStrip(CRGB(0, 0, 0));
            games::leds[tempLed] = CRGB(255, 0, 0);
        }
    }
    if  (!travelling) {
        games::fillStrip(CRGB(0, 0, 0));
        games::leds[curLed] = CRGB(255, 255, 255);
    }
    
}