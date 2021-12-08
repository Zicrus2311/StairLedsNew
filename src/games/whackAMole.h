#pragma once

class whackAMole {
private:
    static bool pressedLastFrame;
    static int curLed;
    static int lastLed;
    static int lastPressTime;
    static bool travelling;

public:
    static void gameLoop();
};