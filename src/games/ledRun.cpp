#include "ledRun.h"

#include "FastLED.h"

#include "games.h"

void ledRun::gameLoop() {
    if(*games::stopDown) {
        games::switchMode(games::Modes::LedRun);
    }

    int ledSpeed = 5000.0/games::numLeds;
    int timeSinceStart = millis() - games::modeBeginTime;
    int onLeds = timeSinceStart/ledSpeed;
    for (int i = 0; i < games::numLeds; i++)
    {
        if(i >= games::numLeds - onLeds)
        {
            games::leds[i] = CRGB(255, 255, 255);
        }
        else{
            games::leds[i] = CRGB(0, 0, 0);
        }
    }
}