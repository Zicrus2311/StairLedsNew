#pragma once

#include <Arduino.h>

struct CHSV;
struct CRGB;

class hsvRgb {
public:
    static CRGB hsv2rgb(CHSV color);
    static CHSV rgb2hsv(CRGB color);
    static CRGB q_hue2rgb(byte hue);
private:
    static float fract(float x);
    static float mix(float a, float b, float t);
    static float step(float e, float x);
};