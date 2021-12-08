#pragma once

struct CRGB;

class games {
private:
    static void fillStrip(const CRGB& color);

public:
    static bool* stopDown;
    static bool* easyDown;
    static bool* mediumDown;
    static bool* hardDown;

    static CRGB* leds;
    static int numLeds;

    enum Modes {
        Rainbow
    };
    static Modes curMode;
    static unsigned long modeBeginTime;

    static void rainbow();

    static void initialize(CRGB* leds, const int& numLeds, bool& stopDown, bool& easyDown, bool& mediumDown, bool& hardDown);
    static void switchMode(const Modes& newMode);
    static void gameLoop();
};