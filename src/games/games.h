#pragma once

struct CRGB;
class LiquidCrystal;

class games {
public:
    static bool* startDown;
    static bool* startPrev;
    static bool* stopDown;
    static bool* stopPrev;

    static CRGB* leds;
    static int numLeds;
    
    static LiquidCrystal* lcd;

    enum Modes {
        Idle,
        LedRun
    };
    static Modes curMode;
    static unsigned long modeBeginTime;

    enum LcdModes {
        Time,
        Speed
    };
    static LcdModes curLcdMode;
    
    static void fillStrip(const CRGB& color);

    static void initialize(bool& startDown, bool& startPrev, bool& stopDown, bool& stopPrev, CRGB* leds, const int& numLeds, LiquidCrystal& lcd);
    static void switchMode(const Modes& newMode);
    static void switchLcdMode(const LcdModes& newLcdMode);
    static void cycleLcdModes();
    static void gameLoop();
};