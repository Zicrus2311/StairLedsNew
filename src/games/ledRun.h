#pragma once

class ledRun {
private:
    static bool started;
    static bool stopped;
    static unsigned long startTime;
    static unsigned long stopTime;
    static unsigned long time;
    static unsigned long lastTime;
    static bool won;

public:
    static void gameLoop();
};